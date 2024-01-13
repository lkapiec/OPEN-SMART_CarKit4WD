/-------------------------------------------------------/
More kits and videos for this Mini ATmega8 are comming soon,
and we will make some videos about using our modules first and upload them to our google drive.
Such as:
DS1307 RTC
DS18B20 temperature sensor
4-Channel touch sensor
8 led bar
Serial MP3 player
I2C 1602 LCD
...
...
...
/-------------------------------------------------------/
When you want to upload code to the ATmega8 on board, you should build the board type for it first.
Arduino IDE Board Type: OPEN SMART ATmega8, you just need to add the follow 17 lines at the end of the doc ...\arduino-1.6.5-r2\hardware\arduino\avr\boards.txt.
############################################################## 
atmega8o.name=OPEN SMART ATmega8 
atmega8o.upload.tool=avrdude 
atmega8o.upload.protocol=arduino 
atmega8o.upload.maximum_size=7680 
atmega8o.upload.maximum_data_size=1024
atmega8o.upload.speed=115200 
atmega8o.bootloader.low_fuses=0xbf 
atmega8o.bootloader.high_fuses=0xdc atmega8o.bootloader.file=optiboot/optiboot_atmega8.hex atmega8o.bootloader.unlock_bits=0x3F 
atmega8o.bootloader.lock_bits=0x0F 
atmega8o.bootloader.tool=avrdude 
atmega8o.build.mcu=atmega8 
atmega8o.build.f_cpu=16000000L 
atmega8o.build.core=arduino:arduino 
atmega8o.build.variant=arduino:standard

Of course you can copy the boards.txt in this compressed package to cover the board.txt in the directory of ...\arduino-1.6.5-r2\hardware\arduino\avr

If you want to use OPEN-SMART AVR ISP Shield or OPEN-SMART Bootloader Programmer to upload bootloader for ATmega8A chip,copy the platform.txt in this 
compressed package to cover the board.txt in the directory of ...\arduino-1.6.5-r2\hardware\arduino\avr, otherwise please skip it.

And then restart the Arduino IDE, so that you can select OPEN SMART ATmega8 board.
