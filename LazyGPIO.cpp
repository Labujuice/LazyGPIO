/*
 * ReadGPIO.cpp
 *
 *  Created on: 2020年5月17日
 *      Author: kenny
 */
#include <Arduino.h>
#include "LazyGPIO.h"



//====================================================================================================
//Class LazyDigiRead
//====================================================================================================
LazyDigiRead::LazyDigiRead()
{
	state = LOW;
	toggle_CallBack = NULL;
	rising_CallBack = NULL;
	falling_CallBack = NULL;
	short_CallBack = NULL;
	long_CallBack = NULL;
}

void LazyDigiRead::init(uint8_t pin, uint8_t type)
{
	inputPin = pin;

	if(type == 0x0 || type == 0x1 || type == 0x2)
	{
		pinMode(pin,type);
	}
	else
	{
		pinMode(pin,INPUT);
	}

}

bool LazyDigiRead::Read(void)
{
	return digitalRead(inputPin);
}

void LazyDigiRead::update(void)
{
	bool new_state = digitalRead(inputPin);

	if(state == new_state)
	{

	}
	else
	{
		//Toggle callback here
		if(toggle_CallBack != NULL)
		{
			toggle_CallBack();
		}

		switch(new_state)
		{
		case HIGH:
			//Rising Callback here
			if(rising_CallBack != NULL)
			{
				rising_CallBack();
			}

			interval = millis() - pressStamp;
			if(interval >= SHORT_PRESS && interval < LONG_PRESS)
			{
				if(short_CallBack != NULL)
				{
					short_CallBack();
				}
			}
			else if(interval >= LONG_PRESS)
			{
				if(long_CallBack != NULL)
				{
					long_CallBack();
				}

			}
			else
			{
				//do nothing
			}
			break;

		case LOW:
			//Falling Callback here
			if(falling_CallBack != NULL)
			{
				falling_CallBack();
			}

			pressStamp = millis();
			break;

		default:
			break;
		}
	}

	state = new_state;
}

void LazyDigiRead::setCallBack(GPIOCallBack_e type,void (*callback_function)(void))
{
	switch(type)
	{
	case Toggle:
		toggle_CallBack = callback_function;
		break;
	case Rising:
		rising_CallBack = callback_function;
		break;
	case Falling:
		falling_CallBack = callback_function;
		break;
	case Short:
		short_CallBack = callback_function;
		break;
	case Long:
		long_CallBack = callback_function;
		break;
	default:
		break;
	}
}

//====================================================================================================
//Class LazyDigiWrite
//====================================================================================================
LazyDigiWrite::LazyDigiWrite()
{
	//Do nothing
}

void LazyDigiWrite::init(uint8_t pin)
{
	outputPin = pin;
	pinMode(outputPin,OUTPUT);
}

void LazyDigiWrite::High(void)
{
	digitalWrite(outputPin,HIGH);
}

void LazyDigiWrite::Low(void)
{
	digitalWrite(outputPin,LOW);
}

void LazyDigiWrite::Toggle(void)
{
	digitalWrite(outputPin,!digitalRead(outputPin));
}


//====================================================================================================
//Class LazyAnalogRead
//====================================================================================================
LazyAnalogRead::LazyAnalogRead()
{
	value = 0;
}

void LazyAnalogRead::init(uint8_t pin)
{
	inputPin = pin;
	pinMode(inputPin,INPUT);
}

int LazyAnalogRead::Read(void)
{
	value = analogRead(inputPin);
	return value;
}
