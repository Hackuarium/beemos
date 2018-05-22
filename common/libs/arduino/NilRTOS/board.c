/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/
/**
 * @file    board.c
 * @brief   Nil RTOS AVR Arduino time ISR.
 *
 * @addtogroup AVR_CORE
 * @{
 */
#include "nil.h"
/** System time ISR. */
NIL_IRQ_HANDLER(TIMER0_COMPA_vect) {

  NIL_IRQ_PROLOGUE();

  nilSysTimerHandlerI();

  NIL_IRQ_EPILOGUE();
}
/**
 * Board-specific initialization code for Arduino.
 * Use timer 0 compare A to geneate an interrupt every 1024 usec.
 *
 */
void boardInit(void) {
  /*
   * Timer 0 setup.
   */
  OCR0A = 128;
  TIMSK0  |= (1 << OCIE0A);  /* IRQ on compare.  */
}
/** @} */