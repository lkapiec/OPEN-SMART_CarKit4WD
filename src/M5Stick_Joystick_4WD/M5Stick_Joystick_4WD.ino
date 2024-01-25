// autor: Lukasz Kapiec
// email: lkapiec@gmail.com
// hardware: MT5STACK_M5Stick_CPlus_1.1 + MT5STACK_RD433T + MT5STACK_JoyC

#include <M5StickCPlus.h>
#include <Wire.h>
#include "RH_ASK.h"
#include "Hat_JoyC.h"

int RF_RX_PIN = 33;  //the RF433 or RF315 receiver module connect with D9 pin of Easy IO Shield pro.
int RF_TX_PIN = 32;  //fake pin

#define TRANSMISION_SPEED 2000
RH_ASK rh_driver(TRANSMISION_SPEED, RF_RX_PIN, RF_TX_PIN, 0);

TFT_eSprite canvas = TFT_eSprite(&M5.Lcd);
JoyC joyc;

#define BUFFER_LENGHT 5
uint8_t buffer[BUFFER_LENGHT] = { 0X7E, 0, 0, 0, 0XEF };  // buffer array for data recieve over serial port

int preX0, preY0;
int nowX0, nowY0;
uint8_t nowKey0, prevKey0;

int preX1, preY1;
int nowX1, nowY1;
uint8_t nowKey1, prevKey1;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(4);

  canvas.createSprite(160, 80);
  canvas.setTextColor(ORANGE);  // Set font colour to orange. 设置字体颜色为橙色
  canvas.setTextSize(1.5);
  joyc.begin();  // Initialize JoyC. 初始化 JoyC

  if (!rh_driver.init())
    Serial.println("RadioHead driver initialization failed!");

  preX0 = joyc.x0;
  preY0 = joyc.y0;
  preX1 = joyc.x1;
  preY1 = joyc.y1;
}

#define SENS 10

#define JOY_BTN_XY_TOLERANCE 20
#define JOY_BTN_X0 100
#define JOY_BTN_Y0 100

uint8_t isChange() {
  uint8_t flag_change = 0;

  nowX0 = joyc.x0;
  if ((nowX0 < (preX0 - SENS)) || nowX0 > (preX0 + SENS)) {
    preX0 = nowX0;
    flag_change = 1;
  }

  nowY0 = joyc.y0;
  if ((nowY0 < (preY0 - SENS)) || nowY0 > (preY0 + SENS)) {
    preY0 = nowY0;
    flag_change = 1;
  }

  nowX1 = joyc.x1;
  if ((nowX1 < (preX1 - SENS)) || nowX1 > (preX1 + SENS)) {
    preX1 = nowX1;
    flag_change = 1;
  }

  nowY1 = joyc.y1;
  if ((nowY1 < (preY1 - SENS)) || nowY1 > (preY1 + SENS)) {
    preY1 = nowY1;
    flag_change = 1;
  }

  nowKey0 = joyc.btn0;
  if (nowKey0 != prevKey0) {
    prevKey0 = nowKey0;
    flag_change = 1;
  }

  nowKey1 = joyc.btn1;
  if (nowKey1 != prevKey1) {
    prevKey1 = nowKey1;
    flag_change = 1;
  }

  return flag_change;
}

char info[100];

#define JOY_BTN_XY_TOLERANCE 40
#define JOY_BTN_X 100
#define JOY_BTN_Y 100

void loop() {
  uint8_t button = 0;  //remote.nowkey;
  int x, y;

  joyc.update();

  if (isChange()) {

    x = map(200 - nowX1, 0, 200, 0, 255);
    y = map(nowY1, 0, 200, 0, 255);

    if (nowX0 < (JOY_BTN_X + JOY_BTN_XY_TOLERANCE) && nowX0 > (JOY_BTN_X - JOY_BTN_XY_TOLERANCE)) {
      if (nowY0 > (JOY_BTN_Y + JOY_BTN_XY_TOLERANCE)) button = 1;
      else if (nowY0 < (JOY_BTN_Y - JOY_BTN_XY_TOLERANCE)) button = 3;
      else button = 0;
    } else if (nowX0 < (JOY_BTN_X - JOY_BTN_XY_TOLERANCE))  // X < 80
    {
      if ((nowY0 < (JOY_BTN_Y + JOY_BTN_XY_TOLERANCE)) && (nowY0 > (JOY_BTN_Y - JOY_BTN_XY_TOLERANCE)))
        button = 2;
    } else  // x > 80
    {
      if ((nowY0 < (JOY_BTN_Y + JOY_BTN_XY_TOLERANCE)) && (nowY0 > (JOY_BTN_Y - JOY_BTN_XY_TOLERANCE)))
        button = 4;
    }

    buffer[1] = (uint8_t)x;
    buffer[2] = (uint8_t)y;
    buffer[3] = (uint8_t)(nowKey0 << 3) | button;

    sprintf(info, "X0: %d Y0: %d BT0: %d, X1: %d Y1: %d BT1: %d, BTN: %d", nowX0, nowY0, nowKey0, nowX1, nowY1, nowKey1, button);
    Serial.println(info);

    rh_driver.send(buffer, BUFFER_LENGHT);
    rh_driver.waitPacketSent();
    delay(200);
  }
}
