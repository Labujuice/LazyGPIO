/*
 * ReadGPIO.cpp
 *
 *  Created on: 2020年5月17日
 *      Author: kenny
 */
#include <Arduino.h>
#include "LazyGPIO.h"


LazyDigiRead::LazyDigiRead()
{
	state = LOW;
	toggle_CallBack = NULL;
	rising_CallBack = NULL;
	falling_CallBack = NULL;
}

void LazyDigiRead::init(uint8_t pin)
{
	inputPin = pin;
	pinMode(pin,INPUT);
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
			break;

		case LOW:
			//Falling Callback here
			if(falling_CallBack != NULL)
			{
				falling_CallBack();
			}
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
	default:
		break;
	}
}
