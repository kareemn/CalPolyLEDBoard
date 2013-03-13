/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012,2013 Giovanni Di Sirio.

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
*/
/*
   Concepts and parts of this file have been contributed by Fabio Utzig.
 */

/**
 * @file    chprintf.c
 * @brief   Mini printf-like functionality.
 *
 * @addtogroup chprintf
 * @{
 */

//#include <stdarg.h>
//#include <Arduino.h>
#include "display.h"
#include "text.h"

// #define MAX_FILLER 11
// #define FLOAT_PRECISION 100000

// typedef int bool_t;
// #define TRUE 1
// #define FALSE 0

volatile int __printf_x, __printf_y;

void chSequentialStreamPut(char c) {
	writeChar(__printf_x, __printf_y, c);
	__printf_x += 6;
}

void testPrint()
{
	__printf_x = 0;
	__printf_y = 24;
	//writeChar(__printf_x, __printf_y, 'H');
	writeChar(0, 24, 'I');
	// char *test = "Hello!";
	// char c;
	// printf_x = 0;
	// printf_y = 24;
	// while ((c = *(test)++))
		// chSequentialStreamPut(c);
}

/**
 * @brief   System formatted output function.
 * @details This function implements a minimal @p printf() like functionality
 *          with output on a @p BaseSequentialStream.
 *          The general parameters format is: %[-][width|*][.precision|*][l|L]p.
 *          The following parameter types (p) are supported:
 *          - <b>x</b> hexadecimal integer.
 *          - <b>X</b> hexadecimal long.
 *          - <b>o</b> octal integer.
 *          - <b>O</b> octal long.
 *          - <b>d</b> decimal signed integer.
 *          - <b>D</b> decimal signed long.
 *          - <b>u</b> decimal unsigned integer.
 *          - <b>U</b> decimal unsigned long.
 *          - <b>c</b> character.
 *          - <b>s</b> string.
 *          .
 *
 * @param[in] chp       pointer to a @p BaseSequentialStream implementing object
 * @param[in] fmt       formatting string
 */
// void chprintf(int x, int y, const char *fmt, ...) {
  // printf_x = x;
  // printf_y = y;
  // va_list ap;
  // char *p, *s, c, filler;
  // int i, precision, width;
  // bool_t is_long, left_align;
  // long l;
// #if CHPRINTF_USE_FLOAT
  // float f;
  // char tmpbuf[2*MAX_FILLER + 1];
// #else
  // char tmpbuf[MAX_FILLER + 1];
// #endif

  // va_start(ap, fmt);
  // while (TRUE) {
    // c = *fmt++;
    // if (c == 0) {
      // va_end(ap);
      // return;
    // }
    // if (c != '%') {
      // chSequentialStreamPut((uint8_t)c);
      // continue;
    // }
    // p = tmpbuf;
    // s = tmpbuf;
    // left_align = FALSE;
    // if (*fmt == '-') {
      // fmt++;
      // left_align = TRUE;
    // }
    // filler = ' ';
    // if (*fmt == '.') {
      // fmt++;
      // filler = '0';
    // }
    // width = 0;
    // while (TRUE) {
      // c = *fmt++;
      // if (c >= '0' && c <= '9')
        // c -= '0';
      // else if (c == '*')
        // c = va_arg(ap, int);
      // else
        // break;
      // width = width * 10 + c;
    // }
    // precision = 0;
    // if (c == '.') {
      // while (TRUE) {
        // c = *fmt++;
        // if (c >= '0' && c <= '9')
          // c -= '0';
        // else if (c == '*')
          // c = va_arg(ap, int);
        // else
          // break;
        // precision *= 10;
        // precision += c;
      // }
    // }
    // /* Long modifier.*/
    // if (c == 'l' || c == 'L') {
      // is_long = TRUE;
      // if (*fmt)
        // c = *fmt++;
    // }
    // else
      // is_long = (c >= 'A') && (c <= 'Z');

    // /* Command decoding.*/
    // switch (c) {
    // case 'c':
      // filler = ' ';
      // *p++ = va_arg(ap, int);
      // break;
    // case 's':
      // filler = ' ';
      // if ((s = va_arg(ap, char *)) == 0)
        // s = "(null)";
      // if (precision == 0)
        // precision = 32767;
      // for (p = s; *p && (--precision >= 0); p++)
        // ;
      // break;
    // case 'D':
    // case 'd':
      // if (is_long)
        // l = va_arg(ap, long);
      // else
        // l = va_arg(ap, int);
      // if (l < 0) {
        // *p++ = '-';
        // l = -l;
      // }
      // p = ltoa(p, l, 10);
      // break;
// #if CHPRINTF_USE_FLOAT
    // case 'f':
      // f = (float) va_arg(ap, double);
      // if (f < 0) {
        // *p++ = '-';
        // f = -f;
      // }
      // p = ftoa(p, f);
      // break;
// #endif
    // case 'X':
    // case 'x':
      // c = 16;
      // goto unsigned_common;
    // case 'U':
    // case 'u':
      // c = 10;
      // goto unsigned_common;
    // case 'O':
    // case 'o':
      // c = 8;
// unsigned_common:
      // if (is_long)
        // l = va_arg(ap, long);
      // else
        // l = va_arg(ap, int);
      // p = ltoa(p, l, c);
      // break;
    // default:
      // *p++ = c;
      // break;
    // }
    // i = (int)(p - s);
    // if ((width -= i) < 0)
      // width = 0;
    // if (left_align == FALSE)
      // width = -width;
    // if (width < 0) {
      // if (*s == '-' && filler == '0') {
        // chSequentialStreamPut((uint8_t)*s++);
        // i--;
      // }
      // do
        // chSequentialStreamPut((uint8_t)filler);
      // while (++width != 0);
    // }
    // while (--i >= 0)
      // chSequentialStreamPut((uint8_t)*s++);

    // while (width) {
      // chSequentialStreamPut((uint8_t)filler);
      // width--;
    // }
  // }
// }

/** @} */
