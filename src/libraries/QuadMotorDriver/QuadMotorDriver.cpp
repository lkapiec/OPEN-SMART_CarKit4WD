#include <Wire.h>
#include "QuadMotorDriver.h"

void QuadMotorDriver::init(uint8_t PWMA, uint8_t PWMB,uint8_t PWMC,uint8_t PWMD)
{

    pwma =PWMA;
    pwmb =PWMB;
	pwmc =PWMC;
	pwmd =PWMD;
	pinMode(pwma,OUTPUT);
	pinMode(pwmb,OUTPUT);
	pinMode(pwmc,OUTPUT);
	pinMode(pwmd,OUTPUT);
	digitalWrite(pwma,LOW);
	digitalWrite(pwmb,LOW);
	digitalWrite(pwmc,LOW);
	digitalWrite(pwmd,LOW);
	Wire.begin();
	stop();
}
void QuadMotorDriver::setSpeed(int8_t speed)
{
	if(speed > 255)speed=255;
	analogWrite(pwma, speed);
    analogWrite(pwmb, speed);
	analogWrite(pwmc, speed);
	analogWrite(pwmd, speed);
}

void QuadMotorDriver::setSpeed(int8_t speed, uint8_t motorID)
{
	if(speed > 255)speed=255;
	switch (motorID)
	{
	  case MOTORA:analogWrite(pwma, speed);
	  	          break;
	  case MOTORB:analogWrite(pwmb, speed);
	  	          break;
	  case MOTORC:analogWrite(pwmc, speed);
	  	          break;
	  case MOTORD:analogWrite(pwmd, speed);
	  	          break;
	  default: break;
	}
}
/**********************************************************************/
/*Function: Get the motor rotate                                  	  */
/*Parameter:-uint8_t direction,Clockwise or anticlockwise;            */
/*          -uint8_t motor_position,MOTORA or MOTORB				  */
/*Return:	void                      							      */
void QuadMotorDriver::rotate(uint8_t direction, uint8_t motorID)
{
	uint8_t newValue = 0;
	if(MOTOR_CLOCKWISE == direction)
	{
		newValue = 0x02;
	}
	else 
	{
		newValue = 0x01;
	}
	switch (motorID)
	{
	  case MOTORA:newValue = newValue;
	              oldDirectionValue &= 0b11111100;
	  	          break;
	  case MOTORB:newValue <<= 2;
	              oldDirectionValue &= 0b11110011;
	  	          break;
	  case MOTORC:newValue <<= 4;
	              oldDirectionValue &= 0b11001111;
				  break;
	  case MOTORD:newValue <<= 6;
	              oldDirectionValue &= 0b00111111;
	  	          break;
	  default: break;
	}
	newValue |= oldDirectionValue;
	Wire.beginTransmission(0x20);
	Wire.write(newValue);
	Wire.endTransmission();
	oldDirectionValue = newValue;
}

void QuadMotorDriver::goForward()
{
	rotate(MOTOR_CLOCKWISE,MOTORA);
	rotate(MOTOR_CLOCKWISE,MOTORB);
	rotate(MOTOR_ANTICLOCKWISE,MOTORC);
	rotate(MOTOR_ANTICLOCKWISE,MOTORD);
}
void QuadMotorDriver::goBackward()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTORA);
	rotate(MOTOR_ANTICLOCKWISE,MOTORB);
	rotate(MOTOR_CLOCKWISE,MOTORC);
	rotate(MOTOR_CLOCKWISE,MOTORD);
}

void QuadMotorDriver::goLeft()
{
	rotate(MOTOR_CLOCKWISE,MOTORA);
	rotate(MOTOR_ANTICLOCKWISE,MOTORB);
	rotate(MOTOR_ANTICLOCKWISE,MOTORC);
	rotate(MOTOR_CLOCKWISE,MOTORD);
}

void QuadMotorDriver::goRight()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTORA);
	rotate(MOTOR_CLOCKWISE,MOTORB);
	rotate(MOTOR_CLOCKWISE,MOTORC);
	rotate(MOTOR_ANTICLOCKWISE,MOTORD);
}

void QuadMotorDriver::goRightFront()
{
	stop(MOTORA);
	rotate(MOTOR_CLOCKWISE,MOTORB);
	stop(MOTORC);
	rotate(MOTOR_ANTICLOCKWISE,MOTORD);
}
void QuadMotorDriver::goLeftFront()
{
	rotate(MOTOR_CLOCKWISE,MOTORA);
	stop(MOTORB);
	rotate(MOTOR_ANTICLOCKWISE,MOTORC);
	stop(MOTORD);
}

void QuadMotorDriver::shaftRight()
{
	rotate(MOTOR_ANTICLOCKWISE,MOTORA);
	stop(MOTORB);
	stop(MOTORC);
	rotate(MOTOR_ANTICLOCKWISE,MOTORD);
}
void QuadMotorDriver::shaftLeft()
{
	rotate(MOTOR_CLOCKWISE,MOTORA);
	stop(MOTORB);
	stop(MOTORC);
	rotate(MOTOR_CLOCKWISE,MOTORD);
}

/*************************************************************/
void QuadMotorDriver::stop()
{
	/*Unenble the pin, to stop the motor. */
	//digitalWrite(pwma,LOW);
	//digitalWrite(pwmb,LOW);
	//digitalWrite(pwmc,LOW);
	//digitalWrite(pwmd,LOW);
	Wire.beginTransmission(0x20);
	Wire.write(0x00);
	Wire.endTransmission();
	oldDirectionValue = 0x00;
}

/*************************************************************/
void QuadMotorDriver::stop(uint8_t motorID)
{
  uint8_t newValue = 0x03;

	switch (motorID)
	{
	  case MOTORA:newValue = newValue;
	  	          break;
	  case MOTORB:newValue <<= 2; 
	  	          break;
	  case MOTORC:newValue <<= 4;
	  	          break;
	  case MOTORD:newValue <<= 6;
	  	          break;
	  default: break;
	}
	newValue = ~newValue;
	newValue &= oldDirectionValue;
	Wire.beginTransmission(0x20);
	Wire.write(newValue);
	Wire.endTransmission();
	oldDirectionValue = newValue;
}

QuadMotorDriver motordriver;
