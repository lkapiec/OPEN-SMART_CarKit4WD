#include "RH_ASK.h"
#include <OS_JoystickCtrl.h>

JoystickCtrl remote;
#define TRANSMISION_SPEED 2000

int RF_TX_PIN = 6;  //connect the sent module to D2 to use you can change it to the idle port you want.
int RF_RX_PIN = 10;  //fake pin

RH_ASK driver(TRANSMISION_SPEED, RF_RX_PIN, RF_TX_PIN, 0);

void setup() 
{
  Serial.begin(115200);
  remote.init();
  if (!driver.init())
    Serial.println("init failed");
}

#define BUFFER_LENGHT 5
uint8_t buffer[BUFFER_LENGHT] = { 0X7E, 0, 0, 0, 0XEF };  // buffer array for data recieve over serial port

void loop() 
{
  int x, y;
  uint8_t xh, xl, yh, yl;
  uint8_t z;

  if (remote.isChange()) 
  {
    x = remote.nowX;
    x = x >> 2;
    y = remote.nowY;
    y = y >> 2;
    z = remote.nowZ;
    z <<= 3;
    uint8_t button = remote.nowkey;
    buffer[1] = x;
    buffer[2] = y;
    buffer[3] = z | button;

    driver.send(buffer, BUFFER_LENGHT);
    driver.waitPacketSent();
    delay(200);
  }
}