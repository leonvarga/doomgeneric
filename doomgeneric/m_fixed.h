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
//	Fixed point arithemtics, implementation.
//


#ifndef __M_FIXED__
#define __M_FIXED__




//
// Fixed point, 32bit as 16.16.
//
#define FRACBITS		16
#define FRACUNIT		(1<<FRACBITS)

typedef int fixed_t;
typedef struct {
	fixed_t x;
	fixed_t y;
} fixed_t_2d;

fixed_t FixedMul	(fixed_t a, fixed_t b);
int FixedMul_batched	(fixed_t* as, fixed_t* bs, fixed_t* res, unsigned int num);
fixed_t_2d FixedMul_batched_2D	(fixed_t as[2], fixed_t bs[2]);
fixed_t FixedMul_batched_1D(fixed_t a, fixed_t b);
int FixedMul_scalar	(fixed_t* as, fixed_t b, fixed_t* res, unsigned int num);
fixed_t FixedDiv	(fixed_t a, fixed_t b);
int FixedDiv_batched	(fixed_t* as, fixed_t* bs, fixed_t* res, unsigned int num);
fixed_t_2d FixedDiv_batched_2D	(fixed_t as[2], fixed_t bs[2]);
fixed_t FixedDiv_batched_1D(fixed_t a, fixed_t b);
int FixedAddOffset_batched	(fixed_t* a, fixed_t offset, fixed_t* res, unsigned int num);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#endif
