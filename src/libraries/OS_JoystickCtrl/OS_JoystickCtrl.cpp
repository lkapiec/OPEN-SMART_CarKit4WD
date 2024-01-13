#include "OS_JoystickCtrl.h"




JoystickCtrl::JoystickCtrl(uint8_t x,uint8_t y,uint8_t z,
		uint8_t key1, uint8_t key2, uint8_t key3, uint8_t key4)
    {
        xPin = x;
		yPin = y;
		zPin = z;
		pinMode(z, INPUT);
        digitalWrite(z, HIGH);
		
        key[0] = key1;
		key[1] = key2;
		key[2] = key3;
		key[3] = key4;
		for(uint8_t i=0; i < 4; i++){
          pinMode(key[i], INPUT);
          digitalWrite(key[i], HIGH);
		}
        
    }
void JoystickCtrl::init()
{
  nowkey = 0;//no button pressed
  prekey = nowkey;
  nowX = getX();
  nowY = getY();
  nowZ = getZ();
  preX = nowX; 
  preY = nowY;
  preZ = nowZ;
}
uint8_t JoystickCtrl::getKey()                        
{
  for(uint8_t i=0; i < 4; i++){
      if(!digitalRead(key[i])){
	  	delay(10);
	  	if(!digitalRead(key[i])) {
            delay(50);
			return (i+1);
		}
      }
	}
//  delay(100);
  return 0;//no button press
}
int JoystickCtrl::getX()
{
  return analogRead(xPin);
}
int JoystickCtrl::getY()
{
  return analogRead(yPin);
}
uint8_t JoystickCtrl::getZ()
{
  if(!digitalRead(zPin)){
  	delay(20);
	if(!digitalRead(zPin))
    return 1;
  }
  return 0;
}
uint8_t JoystickCtrl::isChange()
{
  uint8_t  flag_change = 0;
  nowkey = getKey();
  if(nowkey != prekey)
  {
    prekey = nowkey;
	flag_change = 1;
  }
  nowX = getX();
  if((nowX < (preX-50)) || nowX > (preX+50))
  {
    preX = nowX;
	flag_change = 1;
  }
  nowY = getY();
  if((nowY < (preY-50)) || nowY > (preY+50))
  {
    preY = nowY;
	flag_change = 1;
  }
  nowZ = getZ();
  if(nowZ != preZ)
  {
    preZ = nowZ;
	flag_change = 1;
  }
  return flag_change;
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/