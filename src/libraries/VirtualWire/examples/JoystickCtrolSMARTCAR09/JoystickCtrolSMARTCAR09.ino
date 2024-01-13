/*------------------------------------
// Function: This is car control demo code for Wireless Joystick Remote 
	to control the smart car.
// IDE: Arduinio-1.8.7
// Author: OPEN-SMART Team
// Buy from: https://open-smart.aliexpress.com/store/1199788

-------------------------------------*/
#include <String.h>
#include "QuadMotorDriver.h"
#include <VirtualWire.h>

int RF_RX_PIN = 9; //the RF433 or RF315 receiver module connect with D9 pin of Easy IO Shield pro.
void(* resetFunc) (void) = 0; //software reset when the RF receiver can not respond

//Remote control code macro
#define CMD_INVALID     0
#define CMD_FORWARD     1
#define CMD_TURN_RIGHT 2
#define CMD_SLIDE_RIGHT  3
#define CMD_BACKWARD    4
#define CMD_TURN_LEFT     5
#define CMD_SLIDE_LEFT     6
#define CMD_STOP        7
#define CMD_SPEED_UP    8
#define CMD_SPEED_DOWN  9


#define XY_TOLERANCE 50
#define X0 510//Initial value of X-asix of the Joystick
#define Y0 510//Initial value of Y-asix of the Joystick

#define SPEED_STEPS 20
uint8_t speed0 = 200;//Initial value of speed, value should 0~255.

#define PWMD 11
#define PWMC 6
#define PWMB 5
#define PWMA 3

void setup(){
  motordriver.init(PWMA,PWMB,PWMC,PWMD);
 motordriver.setSpeed(speed0);
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
}
uint8_t command;

uint8_t buffer[VW_MAX_MESSAGE_LEN]; // buffer array for data recieve over serial port 
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void loop(){
  if(vw_get_message(buffer, &buflen)) // non-blocking I/O
  {
    command = decode();
	 if(command != CMD_INVALID){
	controlCar(command);
    }
  }
 
}

void controlCar(uint8_t cmd){
   switch(cmd)
  {
    case CMD_FORWARD: motordriver.goForward();break;
	case CMD_TURN_RIGHT: 
		motordriver.turnRight();
		delay(100); 
		motordriver.stop();
		break;
	case CMD_SLIDE_RIGHT:  
		motordriver.slideRight();
		delay(200); 
		break;
	case CMD_BACKWARD:  motordriver.goBackward();break;
	case CMD_SLIDE_LEFT:   
		motordriver.slideLeft();
		delay(200);
		break;
	case CMD_TURN_LEFT:  
		motordriver.turnLeft();
		delay(100);
		motordriver.stop();
		break;
	case CMD_STOP:        motordriver.stop();break;
	case CMD_SPEED_UP:    speedUp();break;
	case CMD_SPEED_DOWN:  speedDown();break;
	default: break;
  }
}

void speedUp(){
  if(speed0 < 236)speed0 += SPEED_STEPS;
  else speed0 = 255;
  motordriver.setSpeed(speed0);
}

void speedDown(){
  if(speed0 > 70)speed0 -= SPEED_STEPS;
  else speed0 = 50;
   motordriver.setSpeed(speed0);
}


uint8_t decode()
{

   command = 0;
   if((buffer[0]!=0x7E)||(buffer[4]!=0xEF))
  {
	resetFunc();//software reset
	return 0;
  }
  int x,y; 
  int xh,xl,yh,yl;
  uint8_t z;
  uint8_t button;

  x = buffer[1]<<2;
  y = buffer[2]<<2;
  z = buffer[3]>>3;
  button = buffer[3]&0x07;
  
  if((x <(X0+XY_TOLERANCE))&&(x >(X0-XY_TOLERANCE))) 
  {
    if(y > 800)
      command = CMD_FORWARD;
	else if(y < 200)
	  command = CMD_BACKWARD;
	else command = CMD_STOP;
  }
  else if(x < (X0-XY_TOLERANCE))
  {

	if((y <(Y0+XY_TOLERANCE))&&(y >(Y0-XY_TOLERANCE))) 
		command = CMD_SLIDE_LEFT;
  }
  else
  {
	if((y <(Y0+XY_TOLERANCE))&&(y >(Y0-XY_TOLERANCE))) 
		command = CMD_SLIDE_RIGHT;
  }
  switch(button)
  {
    case 1: command = CMD_SPEED_UP;break;//K1 button;
    case 2: command = CMD_TURN_RIGHT;break;//K2 button;
	case 3: command = CMD_SPEED_DOWN;break;//K3 button;
	case 4: command = CMD_TURN_LEFT;break;//K4 button;
	default: break;
  }
  clearBufferArray();
  return command;
}


void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<VW_MAX_MESSAGE_LEN;i++)
    { buffer[i]=0;}                  // clear all index of array with 0
}

