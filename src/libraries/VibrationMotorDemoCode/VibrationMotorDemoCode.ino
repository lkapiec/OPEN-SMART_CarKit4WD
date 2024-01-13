//Demo for Vibration Motor module
//by Open-Smart Team and Catalex Team
//Store: http://www.aliexpress.com/store/1199788
//      http://dx.com
//Demo Function: When the input is HIGH, the motor will vibrate just like your cell phone on silent mode.

#define VibrationMotor 3//the SIG pin of the module is connected with D3 of Arduino / OPEN-SMART UNO
void setup()
{
        Serial.begin(9600);
      	pins_init();
}
void loop()
{
	soundAlarm();
}
void pins_init()
{
	pinMode(VibrationMotor, OUTPUT);
	digitalWrite(VibrationMotor, LOW);
}
											
void soundAlarm()
{

  digitalWrite(VibrationMotor, HIGH);
  delay(400);
  digitalWrite(VibrationMotor, LOW);
  delay(400);
}

