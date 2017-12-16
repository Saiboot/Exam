#ifndef _HEX_TABLE_H
#define _HEX_TABLE_H

#include <stdlib.h>
#include <stdio.h>

#define MAGIC_DIGIT 48
#define MAGIC_CHAR 87

static const char hex_table[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};

/*	getHex:
 *	get the hexadecimal character representation of a integer digit
 *	return: the hexadecimal character.
 */
char getHex(const int digit);

/*	getInt:
 *	get the integer representation of a hexadecimal character
 *	return: the integer.
 */
int getInt(const char hex);

#endif // !_HEX_TABLE_H


