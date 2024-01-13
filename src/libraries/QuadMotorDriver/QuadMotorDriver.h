#ifndef __QUAD_MOTORDRIVER_H__
#define __QUAD_MOTORDRIVER_H__
#include <Arduino.h>
/******Pins definitions*************/

/**************Motor ID**********************/
#define MOTORA 			0
#define MOTORB 			1
#define MOTORC 			2
#define MOTORD 			3

#define MOTOR_CLOCKWISE      0
#define MOTOR_ANTICLOCKWISE  1



/**Class for Motor Shield**/
class QuadMotorDriver
{

	uint8_t MOTORSHIELD_IN1,MOTORSHIELD_IN2,MOTORSHIELD_IN3,MOTORSHIELD_IN4;
	uint8_t SPEEDPIN_A,SPEEDPIN_B;
	uint8_t oldDirectionValue=0;
	uint8_t pwma, pwmb, pwmc, pwmd;
public:
	void init(uint8_t PWMA=3, uint8_t PWMB=5,uint8_t PWMC=6,uint8_t PWMD=9);
	void setSpeed(int8_t speed);
	void setSpeed(int8_t speed, uint8_t motorID);
	void rotate(uint8_t direction, uint8_t motorID);
	void goForward();
	void goBackward();
	void goLeft();
	void goRight();
	void goLeftFront();
	void goRightFront();
    void shaftRight();
	void shaftLeft();
	
	void stop();
	void stop(uint8_t motorID);
};
extern QuadMotorDriver motordriver;

#endif
