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
#include <libed64.h>

#include "../gdbstub.h"

/*
 * Common interrupt handler routine.
 */
void dbg_int_handler(exception_t* e)
{
	// TODO: convert the exception
	dbg_main();
}

volatile unsigned long long rx_buffer[128];
volatile unsigned long long tx_buffer[128];
volatile unsigned char * current_char = ((unsigned char *) rx_buffer) + 512;
volatile unsigned char * current_t_char = ((unsigned char *) tx_buffer) + 512;

int dbg_serial_getc(void)
{
    if (current_char >= ((unsigned char *) rx_buffer) + 512) {
        while (everdrive_receive_buffer_clean());

        // Read 512 bytes into buffer
        everdrive_fifo_read_buffer((void *) rx_buffer, 1);

        // Set pointer to the beginning
        current_char = (volatile unsigned char *) rx_buffer;
    }
	char character = *current_char;
	current_char++;
    return character;
}

int dbg_serial_putchar(int ch)
{
    for (unsigned long i = 0; i < 512; i++) {
        current_t_char[i] = 0;
    }
    current_t_char = (volatile unsigned char *) tx_buffer;
    current_t_char[0] = ch;
	everdrive_fifo_write_buffer(current_t_char, 1);
}

/*****************************************************************************
 * Debugging System Functions
 ****************************************************************************/

/*
 * Write one character to the debugging stream.
 */
int dbg_sys_putchar(int ch)
{
	return dbg_serial_putchar(ch);
}

/*
 * Read one character from the debugging stream.
 */
int dbg_sys_getc(void)
{
	return dbg_serial_getc() & 0xff;
}

/*
 * Read one byte from memory.
 */
int dbg_sys_mem_readb(address addr, char *val)
{
	*val = *(volatile char *)addr;
	return 0;
}

/*
 * Write one byte to memory.
 */
int dbg_sys_mem_writeb(address addr, char val)
{
	*(volatile char *)addr = val;
	return 0;
}

/*
 * Continue program execution.
 */
int dbg_sys_continue(void)
{
	// Return to next instruction
    asm ("mfc0 $2,$14\naddi $2,0x4\nmtc0 $2,$14");
	return 0;
}

/*
 * Single step the next instruction.
 */
int dbg_sys_step(void)
{
	return 0;
}

/*
 * Debugger init function.
 *
 */
void dbg_start(void)
{
	register_exception_handler(dbg_int_handler);
	BREAK;
}
