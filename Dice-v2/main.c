/*
* Dice-v2.c
*
* Created: 10/29/2023 12:05:08 PM
* Author : Marcin Karol Cie?lak
*/

#include "hwconfig.h"

#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>

#include "eemem.h"
#include "ioconfig.h"
#include "display.h"
#include "prng.h"

int main(void)
{
	setup();
	interruptSetup();
	eememInit();
	clock_prescale_set(clock_div_32);
	while (1)
	{
		eventReq |= _BV(EVREQ_BUTT);
		set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep();
		if (eventReq & _BV(EVREQ_DISP))
		{
			eventReq &= ~(_BV(EVREQ_DISP));
			// Run the LCG loop
			do
			{
				
				#ifdef DEBUG
				// Toggle signal pin in debug mode
				PORTB ^= _BV(PINB4);
				#endif
				
				prngNext();

				#ifdef DEBUG
				// Toggle signal pin in debug mode
				PORTB ^= _BV(PINB4);
				#endif
				
			} while (!(PINB & _BV(PINB3)));
			
			// Set the display and wait for timer interrupt
			setDisplay((prngParamsHot.seed % 6) + 1);
			timerStart();
			set_sleep_mode(SLEEP_MODE_IDLE);
			do 
			{ sleep(); } while (!(eventReq & _BV(EVREQ_DELAY)));
			eventReq &= ~(_BV(EVREQ_DELAY));
			clearDisplay();
		}
	}
}
