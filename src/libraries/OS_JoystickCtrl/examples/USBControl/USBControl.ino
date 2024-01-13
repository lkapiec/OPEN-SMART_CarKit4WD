 /* HID Joystick Mouse Example*/
 //Store: http://www.aliexpress.com/store/1199788
 // 	 http://dx.com
 //IDE version: 1.6.5
 //Function: use the joystick control and ATmega32u4 Leonardo board to play PC game: Tetris
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

int vertZero, horzZero;  // Stores the initial value of each axis, usually around 512
int vertValue, horzValue;  // Stores current analog output of each axis
const int sensitivity = 200;  // Higher sensitivity value = slower mouse, should be <= about 500
int mouseClickFlag = 0;

void setup()
{
  Mouse.begin();
  Keyboard.begin();
  remote.init();
  
  delay(1000);  // short delay to let outputs settle
  vertZero = remote.getY();  // get the initial values
  horzZero = remote.getX();  // Joystick should be in neutral position when reading these

}

void loop()
{
  vertValue = vertZero-remote.getY();  // read vertical offset
  horzValue = remote.getX() - horzZero;  // read horizontal offset
  
  if (vertValue != 0)
    Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
  if (horzValue != 0)
    Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
    
  if ((remote.getZ()) && (!mouseClickFlag))  // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // click the left button down
  }
  else if ((!remote.getZ())&&(mouseClickFlag)) // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }
  uint8_t key = remote.getKey();
  switch(key)
  {
    case 1: Keyboard.press(KEY_UP_ARROW);break;
    case 2: Keyboard.press(KEY_RIGHT_ARROW);break;
    case 3: Keyboard.press(KEY_DOWN_ARROW);break;
    case 4: Keyboard.press(KEY_LEFT_ARROW);break;
    default: Keyboard.releaseAll();break;
    }
}
