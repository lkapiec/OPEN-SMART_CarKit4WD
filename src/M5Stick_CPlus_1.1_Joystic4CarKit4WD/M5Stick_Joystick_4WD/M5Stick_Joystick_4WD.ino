// autor: Lukasz Kapiec
// email: lkapiec@gmail.com
// hardware: MT5STACK_M5Stick_CPlus_1.1 + MT5STACK_RD433T + MT5STACK_JoyC

#define JOY_ADDR 0x38

#include <M5StickCPlus.h>
#include <Wire.h>
#include "RH_ASK.h"

int RF_RX_PIN = 33;  //the RF433 or RF315 receiver module connect with D9 pin of Easy IO Shield pro.
int RF_TX_PIN = 32;  //fake pin

const unsigned int BCKGRDCOL = M5.Lcd.color565(138, 235, 244);

#define TRANSMISION_SPEED 2000
RH_ASK rh_driver(TRANSMISION_SPEED, RF_RX_PIN, RF_TX_PIN, 0);

#define BUFFER_LENGHT 5
uint8_t buffer[BUFFER_LENGHT] = { 0X7E, 0, 0, 0, 0XEF };  // buffer array for data recieve over serial port


void setup() {
  M5.begin();
  Wire.begin(0, 26, 100000UL);
  // clear the background
  M5.Lcd.setRotation(2);
  M5.Lcd.fillScreen(BCKGRDCOL);
  //M5.Lcd.fillRect(0, 0, 135, 240, BLACK);


  if (!rh_driver.init())
    Serial.println("RadioHead driver initialization failed!");
}

void loop() {
  int x, y;
  uint8_t xh, xl, yh, yl;
  uint8_t z;

  //if (remote.isChange())
  //{
  x = 510;  //remote.nowX;
  x = x >> 2;
  y = 804;  //remote.nowY;
  y = y >> 2;
  z = 0;  //remote.nowZ;
  z <<= 3;
  uint8_t button = remote.nowkey;
  buffer[1] = x;
  buffer[2] = y;
  buffer[3] = z | button;

  rh_driver.send(buffer, BUFFER_LENGHT);
  rh_driver.waitPacketSent();
  delay(200);
  //}
}

//buffer[1] = 510 >> 2;
//buffer[2] = 804>> 2;
//rh_driver.send(buffer, BUFFER_LENGHT);
//rh_driver.waitPacketSent();
//delay(1000);
//buffer[1] = 510 >> 2;
//buffer[2] = 0;
//rh_driver.send(buffer, BUFFER_LENGHT);
//rh_driver.waitPacketSent();
//delay(1000);
