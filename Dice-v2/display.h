/*
* display.h
*
* Created: 10/29/2023 1:29:03 PM
*  Author: Marcin Karol Cie?lak
*/


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>

#define DICE_1 _BV(PINB0)
#define DICE_2 _BV(PINB1)
#define DICE_3 (DICE_1 | DICE_2)
#define DICE_4 _BV(PINB2)
#define DICE_5 (DICE_1 | DICE_4)
#define DICE_6 (DICE_2 | DICE_4)

inline void setDisplay(uint8_t number)
{
	PORTB |= (number & (DICE_1 | DICE_2 | DICE_4));
}

inline void clearDisplay(void)
{
	PORTB &= ~(DICE_1 | DICE_2 | DICE_4);
}

#endif /* DISPLAY_H_ */