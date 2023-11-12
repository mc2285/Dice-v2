/*
* hwconfig.h
*
* Created: 10/29/2023 2:06:13 PM
*  Author: Marcin Karol Cie?lak
*/


#ifndef HWCONFIG_H_
#define HWCONFIG_H_

#include <avr/io.h>
#include <avr/fuse.h>

// Configure fuses

FUSES = {
	LFUSE_DEFAULT,
	HFUSE_DEFAULT,
};

// Configure (base) CPU frequency according to set fuses
// Please take note that F_CPU varies across the program
// due to divider changes and plan accordingly

#define F_CPU 1200000UL

#endif /* HWCONFIG_H_ */