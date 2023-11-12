/*
* ioconfig.h
*
* Created: 10/29/2023 2:08:38 PM
*  Author: Marcin Karol Cie?lak
*/


#ifndef IOCONFIG_H_
#define IOCONFIG_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "eemem.h"

inline void setup(void)
{
	#ifndef DEBUG

	// Set pins 0, 1, 2 as output
	DDRB = (_BV(PINB0) | _BV(PINB1) | _BV(PINB2));

	// Enable pull-up on the button pin and the unused pin
	PORTB |= (_BV(PINB3) | _BV(PINB4));

	#else
	
	// Set pins 0, 1, 2, 4 as output
	DDRB = (_BV(PINB0) | _BV(PINB1) | _BV(PINB2) | _BV(PINB4));

	// Enable pull-up on the button pin
	PORTB |= (_BV(PINB3));
	
	#endif
	
	// Disable ADC
	PRR |= _BV(PRADC);
	
	// Disable Analog Comparator
	ACSR |= _BV(ACD);
}

// Bit 0 - request generating a new number and displaying it
// Bit 1 - display delay over
// Bit 2 - currently waiting for button
volatile uint8_t eventReq, timerEventCnt;
#define EVREQ_DISP 0
#define EVREQ_DELAY 1
#define EVREQ_BUTT 2

inline void interruptSetup(void)
{
	// Unmask PCINT0
	GIMSK |= _BV(PCIE);
	
	// Enable PCINT3 (button pin)
	PCMSK |= _BV(PCINT3);
	
	// Unmask TIM0_OVF
	TIMSK0 |= _BV(TOIE0);
	
	eventReq = 0x00;
	timerEventCnt = 0x00;
}

inline void safeSei(void)
{
	// Clear the PCIF flag by writing 1 and then enable interrupts
	GIFR |= _BV(PCIF);
	TIFR0 |= _BV(TOV0);
	sei();
}

inline void sleep(void)
{
	sleep_enable();
	safeSei();
	sleep_cpu();
	// Wakes up from interrupt here
	cli();
	sleep_disable();
}

inline void timerStart(void)
{
	TCNT0 = 0x00;
	// Start clock with divider 256
	TCCR0B |= (_BV(CS00) | _BV(CS01));
}

inline void timerStop(void)
{
	// Disable TCNT0 clock
	TCCR0B &= ~(_BV(CS00) | _BV(CS01));
}

ISR(PCINT0_vect)
{
	if (!(PINB & _BV(PINB3)) && (eventReq & _BV(EVREQ_BUTT)))
	{
		eventReq &= ~_BV(EVREQ_BUTT);
		eventReq |= _BV(EVREQ_DISP);
	}
}

ISR(TIM0_OVF_vect)
{
	if (++timerEventCnt >= onDelayHot)
	{
		timerStop();
		timerEventCnt = 0x00;
		eventReq |= _BV(EVREQ_DELAY);
		sleep_disable();
	}
}

#endif /* IOCONFIG_H_ */