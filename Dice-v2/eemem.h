/*
* eemem.h
*
* Created: 10/29/2023 3:30:01 PM
*  Author: Marcin Karol Cie?lak
*/


#ifndef EEMEM_H_
#define EEMEM_H_

#include <avr/eeprom.h>

typedef struct {
	uint32_t modulus;
	uint32_t multiplier;
	uint32_t seed;
} ee_prng_param_t;

ee_prng_param_t EEMEM prngParams = {
	4093,
	209,
	17
};

uint8_t EEMEM onDelay = 20;

uint8_t onDelayHot;
ee_prng_param_t prngParamsHot;

// Load EEPROM config into RAM
inline void eememInit(void)
{
	eeprom_read_block(&prngParamsHot, &prngParams, sizeof(prngParams));
	eeprom_read_block(&onDelayHot, &onDelay, sizeof(onDelay));
}


#endif /* EEMEM_H_ */