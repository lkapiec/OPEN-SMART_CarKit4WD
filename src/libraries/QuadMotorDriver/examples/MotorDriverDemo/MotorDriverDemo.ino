
#include "QuadMotorDriver.h"

#define PIN_PWMA 3
#define PIN_PWMB 5
#define PIN_PWMC 6
#define PIN_PWMD 11
uint8_t speed0 = 250;
#define SPEED_STEPS 50
void setup(){
  motordriver.init(PIN_PWMA,PIN_PWMB,PIN_PWMC,PIN_PWMD);	
  motordriver.setSpeed(speed0);
  
}


void loop(){
	testMotor();
}


void testMotor()
{
  motordriver.rotate(MOTORA,MOTOR_CLOCKWISE);
  delay(1000);
  motordriver.rotate(MOTORA,MOTOR_ANTICLOCKWISE);
  delay(1000);
  motordriver.stop();
  motordriver.rotate(MOTORB,MOTOR_CLOCKWISE);
  delay(1000);
  motordriver.rotate(MOTORB,MOTOR_ANTICLOCKWISE);
  delay(1000);
  motordriver.stop();
  motordriver.rotate(MOTORC,MOTOR_CLOCKWISE);
  delay(1000);
  motordriver.rotate(MOTORC,MOTOR_ANTICLOCKWISE);
  delay(1000);
  motordriver.stop();
  motordriver.rotate(MOTORD,MOTOR_CLOCKWISE);
  delay(1000);
  motordriver.rotate(MOTORD,MOTOR_ANTICLOCKWISE);
  delay(1000);
  motordriver.stop();
}
void speedUp(){
  if(speed0 < 200)speed0 += SPEED_STEPS;
  else speed0 = 250;
  motordriver.setSpeed(speed0);
}

void speedDown(){
  if(speed0 > 50)speed0 -= SPEED_STEPS;
  else speed0 = 0;
   motordriver.setSpeed(speed0);
}
