#include "hex.h"


char getHex(int digit)
{
	return hex_table[digit];
}

int getInt(char hex)
{
	if ((int)hex <= 57)
		return ((int)hex - MAGIC_NUM);

	return ((int)hex - MAGIC_CHAR);
}

void getHexSubsets(int **subs, int *elements)
{
	subs = malloc(sizeof(int *));
	int e = 0;

	for (size_t a = 0; a < 16; a++)
		for (size_t b = 0; b < 16; b++)
			for (size_t c = 0; c < 16; c++)
				for (size_t d = 0; d < 16; d++)
				{
					if (a + b + c + d == 30)
					{
						if (a == b || a == c || a == d || b == c || b == d || c == d)
							continue;

						if(e)
							realloc(subs, sizeof(int *) * (e + 1));

						subs[e] = malloc(sizeof(int) * 4);

						subs[e][0] = a;
						subs[e][1] = b;
						subs[e][2] = c;
						subs[e][3] = d;
						e++;

						for (size_t i = 0; i < e; i++)
						{
							printf("%d %d %d %d\n", subs[i][0], subs[i][1], subs[i][2], subs[i][3]);
						}

					}
				}
	*elements = e;
}