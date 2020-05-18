/*
 * ReadGPIO.h
 *
 *  Created on: 2020年5月17日
 *      Author: kenny
 */

#ifndef LAZYGPIO_H_
#define LAZYGPIO_H_

enum GPIOCallBack_e
{
	Toggle = 0,
	Rising = 1,
	Falling = 2
};

class LazyDigiRead
{
public:
	LazyDigiRead();
	void init(uint8_t pin, uint8_t type);
	bool Read(void);
	void update(void);

	void setCallBack(GPIOCallBack_e type,void (*callback_function)(void));

	bool state;
private:
	void (*toggle_CallBack)(void);
	void (*rising_CallBack)(void);
	void (*falling_CallBack)(void);
	uint8_t inputPin;
};

class LazyDigiWrite
{
public:
	LazyDigiWrite();
	void init(uint8_t pin);
	void High(void);
	void Low(void);
	void Toggle(void);

private:
	uint8_t outputPin;
};

class LazyAnalogRead
{
public:
	LazyAnalogRead();
	void init(uint8_t pin);
	int Read(void);

	int value;
private:
	uint8_t inputPin;
};


#endif /* LAZYGPIO_H_ */
