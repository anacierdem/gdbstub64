/*
 * Copyright (C) 2016  Matt Borgerson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <libdragon.h>

/* Define the size_t type */
#define DBG_DEFINE_SIZET 1

/* Define required standard integer types (e.g. uint16_t) */
#define DBG_DEFINE_STDINT 1

/*****************************************************************************
 * Types
 ****************************************************************************/

#if DBG_DEFINE_STDINT
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;
#endif

#if DBG_DEFINE_SIZET
typedef unsigned int size_t;
#endif

typedef unsigned int address;
typedef unsigned int reg;

#define BREAK asm volatile ("break")

enum DBG_REGISTER {
	DBG_CPU_VR4300_REG_ZERO       = 0,
	DBG_CPU_VR4300_REG_AT       = 1,
	DBG_CPU_VR4300_REG_V0       = 2,
	DBG_CPU_VR4300_REG_V1       = 3,
	DBG_CPU_VR4300_REG_A0       = 4,
	DBG_CPU_VR4300_REG_A1       = 5,
	DBG_CPU_VR4300_REG_A2       = 6,
	DBG_CPU_VR4300_REG_A3       = 7,
	DBG_CPU_VR4300_REG_T0       = 8,
	DBG_CPU_VR4300_REG_T1       = 9,
	DBG_CPU_VR4300_REG_T2       = 10,
	DBG_CPU_VR4300_REG_T3       = 11,
	DBG_CPU_VR4300_REG_T4       = 12,
	DBG_CPU_VR4300_REG_T5       = 13,
	DBG_CPU_VR4300_REG_T6       = 14,
	DBG_CPU_VR4300_REG_T7       = 15,
	DBG_CPU_VR4300_REG_S0       = 16,
	DBG_CPU_VR4300_REG_S1       = 17,
	DBG_CPU_VR4300_REG_S2       = 18,
	DBG_CPU_VR4300_REG_S3       = 19,
	DBG_CPU_VR4300_REG_S4       = 20,
	DBG_CPU_VR4300_REG_S5       = 21,
	DBG_CPU_VR4300_REG_S6       = 22,
	DBG_CPU_VR4300_REG_S7       = 23,
	DBG_CPU_VR4300_REG_T8       = 24,
	DBG_CPU_VR4300_REG_T9       = 25,
	DBG_CPU_VR4300_REG_K0       = 26,
	DBG_CPU_VR4300_REG_K1       = 27,
	DBG_CPU_VR4300_REG_GP       = 28,
	DBG_CPU_VR4300_REG_SP       = 29,
	DBG_CPU_VR4300_REG_FP       = 30,
	DBG_CPU_VR4300_REG_RA       = 31,
	DBG_CPU_VR4300_NUM_REGISTERS 	= 32
};

struct dbg_state {
	int signum;
	reg registers[DBG_CPU_VR4300_NUM_REGISTERS];
};

/*****************************************************************************
 * Prototypes
 ****************************************************************************/

void dbg_interrupt(exception_t* e);
void dbg_start(void);