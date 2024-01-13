#include <VirtualWire.h>
#include <OS_JoystickCtrl.h>

JoystickCtrl remote;
int RF_TX_PIN = 6;//connect the sent module to D2 to use  
              //you can change it to the idle port you want. 
 
void setup()
{
  
  Serial.begin(9600);
  remote.init();
  vw_set_tx_pin(RF_TX_PIN); // Setup transmit pin
  vw_setup(2000); // Transmission speed in bits per second.
}

uint8_t buffer[4]= {0X7E,0,0,0XEF}; // buffer array for data recieve over serial port 

void loop()
{
  
   
    
 int x,y; 
 uint8_t xh,xl,yh,yl;
  uint8_t z;
  if(remote.isChange())
  {
    x=remote.nowX;
	x = x>>5;
    y=remote.nowY;
    y = y>>5;
    z=remote.nowZ;
	z <<= 5;
  uint8_t button = remote.nowkey;
  button <<=5;
  uint8_t i = 0;
    buffer[1] = x | z;
    buffer[2] = y | button;
  Serial.print("x = ");
  Serial.print(x ,DEC);
  Serial.print(","); 
  Serial.print("y = ");
  Serial.print(y ,DEC);
  Serial.print(","); 
  Serial.print("z = ");
  Serial.print(z ,DEC);
  Serial.print(","); 
  if(button)
    {
      Serial.print("KEY");
      Serial.println(button);
    }
    else Serial.println("NO KEY");
  vw_send(buffer, 4);  // 
    delay(100);//between two message, you should delay 400ms so that the receiver may not miss it.
  }

 
}


