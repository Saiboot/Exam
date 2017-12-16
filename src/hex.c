#include "hex.h"


char getHex(const int digit)
{
	return hex_table[digit];
}

int getInt(const char hex)
{
	/* ASCII TABLE MANIPULATION */

	if ((int)hex <= 57)
		return ((int)hex - MAGIC_DIGIT);

	return ((int)hex - MAGIC_CHAR);
}
