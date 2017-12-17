#include "square.h"

void print_square(int **squares, int index)
{
	printf("\n");
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			printf("[%c]", getHex(squares[index][j + (4 * i)]));
		}
		printf("\n");
	}
	printf("\n");
}
