#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

int gpioPin =4;  
uint32 databuf;



uint8 readSensorData(void)
{
	uint8 crc; 
	uint8 i;

	pinMode(gpioPin,OUTPUT); 
	digitalWrite(gpioPin, 0); 
	delay(25);
	digitalWrite(gpioPin, 1); 
	pinMode(gpioPin, INPUT); 
	pullUpDnControl(gpioPin,PUD_UP);

	delayMicroseconds(27);
	if(digitalRead(gpioPin)==0) 
	{
		while(!digitalRead(gpioPin)); 

		for(i=0;i<32;i++)
		{
			while(digitalRead(gpioPin)); 
			while(!digitalRead(gpioPin)); 
			delayMicroseconds(HIGH_TIME);
			databuf*=2;
			if(digitalRead(gpioPin)==1) 
			{
				databuf++;
			}
		}

		for(i=0;i<8;i++)
		{
			while(digitalRead(gpioPin)); 
			while(!digitalRead(gpioPin)); 
			delayMicroseconds(HIGH_TIME);
			crc*=2;  
			if(digitalRead(gpioPin)==1) 
			{
				crc++;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int main (int argc, char **argv)
{

	if (argc != 2) {
		printf("usage: %s GPIOpin#\n", argv[0]);
		printf("example: %s 1 - Read from wiringPi GPIO #1\n", argv[0]);
		return 2;
	}

	gpioPin = atoi(argv[1]);

	if (gpioPin <= 0) {
		printf("Please select a valid GPIO pin #\n");
		return 3;
	}


	printf("Use GPIO%d to read data!\n",gpioPin);

	if (-1 == wiringPiSetup()) {
		printf("Setup wiringPi failed!");
		return 1;
	}

	pinMode(gpioPin, OUTPUT); 
	digitalWrite(gpioPin, 1); 

	while(1) {
		pinMode(gpioPin,OUTPUT); 
		digitalWrite(gpioPin, 1); 
		delay(3000);
		if(readSensorData())
		{
			printf("Success! Sensor data read ok!\n");
			printf("Hum=%d.%d\%\n",(databuf>>24)&0xff,(databuf>>16)&0xff); 
			printf("Temp=%d.%dC\n",(databuf>>8)&0xff,databuf&0xff);
			databuf=0;
			break;
		}
		else
		{
			
			databuf=0;
		}
	}
	return 0;
}

