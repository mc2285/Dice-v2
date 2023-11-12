/*
* prng.h
*
* Created: 10/29/2023 3:29:37 PM
*  Author: Marcin Karol Cie?lak
*/


#ifndef PRNG_H_
#define PRNG_H_

#include "eemem.h"

inline void prngNext(void)
{
	prngParamsHot.seed = (prngParamsHot.multiplier * prngParamsHot.seed) % prngParamsHot.modulus;
}

#endif /* PRNG_H_ */