/*------------------------------------
// Function: This is car control demo code for Wireless Joystick Remote to control the smart car.
// IDE: Arduinio-2.2.1
// Author: OPEN-SMART Team
// Author: Lukasz Kapiec
// Buy from: https://open-smart.aliexpress.com/store/1199788
-------------------------------------*/

#include "QuadMotorDriver.h"
#include "RH_ASK.h"

void (*resetFunc)(void) = 0; //software reset when the RF receiver can not respond

int RF_RX_PIN = 9;   //the RF433 or RF315 receiver module connect with D9 pin of Easy IO Shield pro.
int RF_TX_PIN = 10;  //fake pin

#define TRANSMISION_SPEED 2000
RH_ASK rh_driver(TRANSMISION_SPEED, RF_RX_PIN, RF_TX_PIN, 0);

//Remote control code macro
enum COMMAND_CONTROL {CMD_INVALID = 0, CMD_FORWARD, CMD_TURN_RIGHT, CMD_SLIDE_RIGHT, CMD_BACKWARD, 
CMD_TURN_LEFT, CMD_SLIDE_LEFT,CMD_STOP, CMD_SPEED_UP,CMD_SPEED_DOWN,CMD_JOYSTIC_BUTTON};

#define XY_TOLERANCE 50
#define X0 510  //Initial value of X-asix of the Joystick
#define Y0 510  //Initial value of Y-asix of the Joystick

#define SPEED_STEPS 20
uint8_t speed0 = 200;  //Initial value of speed, value should 0~255.

#define PWMD 11
#define PWMC 6
#define PWMB 5
#define PWMA 3

#define MAX_MESSAGE_LEN RH_ASK_MAX_MESSAGE_LEN
uint8_t buflen = MAX_MESSAGE_LEN;
uint8_t buffer[MAX_MESSAGE_LEN];  // buffer array for data recieve over serial port

void setup() 
{
  Serial.begin(115200);
  
  motordriver.init(PWMA, PWMB, PWMC, PWMD);
  motordriver.setSpeed(speed0);
  
  if (!rh_driver.init())
    Serial.println("RadioHead driver initialization failed!");
}

void loop() 
{
  if(rh_driver.recv(buffer, &buflen))  // Non-blocking
  {
    uint8_t command;
    command = decode();
    if (command != CMD_INVALID) {
      controlCar(command);
    }
  }
}

void controlCar(uint8_t cmd) 
{  
  switch (cmd) 
  {
    case CMD_FORWARD:
      motordriver.goForward();
      break;
    
    case CMD_TURN_RIGHT:
      motordriver.turnRight();
      delay(100);
      motordriver.stop();
      break;
    
    case CMD_SLIDE_RIGHT:
      motordriver.slideRight();
      delay(200);
      break;
    
    case CMD_BACKWARD: 
      motordriver.goBackward(); 
      break;
    
    case CMD_SLIDE_LEFT:
      motordriver.slideLeft();
      delay(200);
      break;
    
    case CMD_TURN_LEFT:
      motordriver.turnLeft();
      delay(100);
      motordriver.stop();
      break;
    
    case CMD_STOP: 
      motordriver.stop(); 
      break;
    
    case CMD_SPEED_UP: 
      speedUp(); 
      break;
    
    case CMD_SPEED_DOWN: 
      speedDown(); 
      break;
    
    default: 
      break;
  }
}

void speedUp() 
{
  if (speed0 < 236) 
    speed0 += SPEED_STEPS;
  else speed0 = 255;
  motordriver.setSpeed(speed0);
}

void speedDown() 
{
  if (speed0 > 70) speed0 -= SPEED_STEPS;
  else speed0 = 50;
  motordriver.setSpeed(speed0);
}

uint8_t decode() 
{
  int x, y;
  int xh, xl, yh, yl;
  uint8_t z;
  uint8_t button;
  uint8_t joystic_button;
  uint8_t command = CMD_INVALID;
    
  if ((buffer[0] != 0x7E) || (buffer[4] != 0xEF)) 
  {
    resetFunc();  //software reset
    return command;
  }

  x = buffer[1] << 2;
  y = buffer[2] << 2;
  z = buffer[3] >> 3;
  button = buffer[3] & 0x07;
  joystic_button = z & 1;

  if ((x < (X0 + XY_TOLERANCE)) && (x > (X0 - XY_TOLERANCE))) 
  {
    if (y > 800) command = CMD_FORWARD;
    else if (y < 200) command = CMD_BACKWARD;
    else command = CMD_STOP;
  } else if (x < (X0 - XY_TOLERANCE)) 
  {
    if ((y < (Y0 + XY_TOLERANCE)) && (y > (Y0 - XY_TOLERANCE)))
      command = CMD_SLIDE_LEFT;
  } else 
  {
    if ((y < (Y0 + XY_TOLERANCE)) && (y > (Y0 - XY_TOLERANCE)))
      command = CMD_SLIDE_RIGHT;
  }

  switch (button) 
  {
    case 1: //K1 button
      command = CMD_SPEED_UP; 
      break;    
    case 2: //K2 button;
      command = CMD_TURN_RIGHT; 
      break;
    case 3: //K3 button;
      command = CMD_SPEED_DOWN; 
      break;
    case 4: //K4 button;
      command = CMD_TURN_LEFT; 
      break;
    default: 
      break;
  }
  
  clearBufferArray();
  
  return command;
}

void clearBufferArray()  // function to clear buffer array
{
  for (int i = 0; i < buflen; i++) 
    buffer[i] = 0; 
}