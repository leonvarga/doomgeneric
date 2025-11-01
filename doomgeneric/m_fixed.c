//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	Fixed point implementation.
//

// Modified 
// @author Leon Varga
// @date Oct-2025
//
// We have to map the used fixed point representation to the NPU representation.
// 32bit fixed_point -> 16 bit floating point
//
// In addition, we have to handle the PCIe overhead by collecting batches of operations.
// single FixedMul -> batched FixedMul
//

#include "stdlib.h"

#include "doomtype.h"
#include "i_system.h"

#include "m_fixed.h"


// Fixme. __USE_C_FIXED__ or something.

fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )
{
	float frac = 65536.0;
	float d_a = ((float) a) / frac;
	double d_b = ((double) b) / frac;
    // printf("- %f x %f\n", d_a, d_b);
    return ((int64_t) a * (int64_t) b) >> FRACBITS;
}



// Just a private copy for refactoring
fixed_t
_FixedMul
( fixed_t	a,
  fixed_t	b )
{
	float frac = 65536.0;
	float d_a = ((float) a) / frac;
	double d_b = ((double) b) / frac;
    // printf("+ %f x %f\n", d_a, d_b);
    return ((int64_t) a * (int64_t) b) >> FRACBITS;
}



int FixedMul_batched(fixed_t* as, fixed_t* bs, fixed_t* res, unsigned int num) 
{
	for (int i=0; i < num; i++) {
    		res[i] = _FixedMul(as[i], bs[i]);
	}

	return num;
}

//
// FixedDiv, C version.
//

fixed_t FixedDiv(fixed_t a, fixed_t b)
{
    if ((abs(a) >> 14) >= abs(b))
    {
	return (a^b) < 0 ? INT_MIN : INT_MAX;
    }
    else
    {
	int64_t result;

	result = ((int64_t) a << 16) / b;

	return (fixed_t) result;
    }
}

// Just a private copy for refactoring
fixed_t _FixedDiv(fixed_t a, fixed_t b)
{
    if ((abs(a) >> 14) >= abs(b))
    {
	return (a^b) < 0 ? INT_MIN : INT_MAX;
    }
    else
    {
	int64_t result;

	result = ((int64_t) a << 16) / b;

	return (fixed_t) result;
    }
}

int FixedDiv_batched(fixed_t* as, fixed_t* bs, fixed_t* res, unsigned int num) 
{
	for (int i=0; i < num; i++) {
    		res[i] = _FixedDiv(as[i], bs[i]);
	}

	return num;
}

int FixedAddOffset_batched(fixed_t* as, fixed_t offset, fixed_t* res, unsigned int num) 
{
	for (int i=0; i < num; i++) {
    		res[i] = as[i] + offset;
	}

	return num;
}
