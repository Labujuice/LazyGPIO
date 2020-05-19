/*
 * ReadGPIO.h
 *
 *  Created on: 2020年5月17日
 *      Author: kenny
 */

#ifndef LAZYGPIO_H_
#define LAZYGPIO_H_

#define SHORT_PRESS 10
#define LONG_PRESS 1000

enum GPIOCallBack_e
{
	Toggle = 0,
	Rising = 1,
	Falling = 2,
	Short = 3,
	Long = 4
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
	void (*short_CallBack)(void);
	void (*long_CallBack)(void);
	uint8_t inputPin;
	uint32_t pressStamp,interval;

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
