#ifndef _HEX_TABLE_H
#define _HEX_TABLE_H

#include <stdlib.h>
#include <stdio.h>

#define MAGIC_CHAR 87
#define MAGIC_NUM 48

static const char hex_table[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};


char getHex(int digit);

int getInt(char hex);

void getHexSubsets(int **subs, int *elements);

#endif // !_HEX_TABLE_H


