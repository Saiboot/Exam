#include "hex.h"


char getHex(int digit)
{
	return hex_table[digit];
}

void getHexSubsets(int **subs, int *elements)
{
	int **subsets = malloc(sizeof(int *));
	int e = 0;

	for (size_t a = 0; a < 16; a++)
		for (size_t b = 0; b < 16; b++)
			for (size_t c = 0; c < 16; c++)
				for (size_t d = 0; d < 16; d++)
				{
					if (a + b + c + d == 30)
					{
						realloc(subsets, sizeof(int *) * (e + 1));
						subsets[e] = malloc(sizeof(int) * 4);

						subsets[e][0] = a;
						subsets[e][1] = b;
						subsets[e][2] = c;
						subsets[e][3] = d;
						e++;
					}
				}

	return subsets;
}