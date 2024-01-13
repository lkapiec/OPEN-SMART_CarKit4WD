#ifndef _OPENSMART_JOYSTICKCTRL_H__
#define _OPENSMART_JOYSTICKCTRL_H__

#include <Arduino.h>


class JoystickCtrl{

private:

    uint8_t key[4];
	uint8_t prekey;
	
    uint8_t xPin, yPin, zPin;
	int preX, preY;
	uint8_t preZ;
public:

    JoystickCtrl(uint8_t x=A0,uint8_t y=A1,uint8_t z=7,
		uint8_t key1 = 5, uint8_t key2 = 4, uint8_t key3 = 3, uint8_t key4 =2);
	void init();
    uint8_t getKey();                        
    int getX();
	int getY();
	uint8_t getZ();
	uint8_t isChange();
	
	uint8_t nowkey;
	int nowX, nowY;
	uint8_t nowZ;
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/