//Store: http://www.aliexpress.com/store/1199788
 // 	 http://dx.com
 // board: OPEN-SMART UNO R3
 //IDE version: 1.6.5
 //Function: use the serial monitor to tell the movement of Joystick Control 
/***************************************/


#include <OS_JoystickCtrl.h>

uint8_t horzPin = A0;  // x pin Analog output of horizontal joystick pin
uint8_t vertPin = A1;  //y pin  Analog output of vertical joystick pin
uint8_t selPin = 7;  // z pin select button pin of joystick
uint8_t key1 = 5;
uint8_t key2 = 4;
uint8_t key3 = 3;
uint8_t key4 = 2;

JoystickCtrl remote(horzPin, vertPin,selPin, key1, key2, key3, key4);

void setup()
{
  remote.init();
  Serial.begin(9600); // 9600 bps
  Serial.println("start");
}

void loop()

{
  int x,y; 
  uint8_t z;
  if(remote.isChange())
  {
    x=remote.nowX;
    y=remote.nowY;
    z=remote.nowZ;
  Serial.print("x = ");
  Serial.print(x ,DEC);
  Serial.print(" y = ");
  Serial.print(y ,DEC);
  Serial.print(" z = ");
  Serial.println(z ,DEC);
  uint8_t button = remote.nowkey;
  if(button)
    {
      Serial.print("KEY");
      Serial.println(button);
    }
    else Serial.println("NO KEY");
  }
  delay(100);
}


