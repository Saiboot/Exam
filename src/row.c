#include "row.h"

int unique_row(int *row1, int *row2)
{
	for (unsigned int i = 0; i < ROW_ELEMS; i++)
	{
		for (unsigned int j = 0; j < ROW_ELEMS; j++)
		{
			if (row1[i] == row2[j])
				return 0;
		}
	}

	return 1;
}

int valid_row(int e1, int e2, int e3, int e4)
{
	return !(e1 == e2 || e1 == e3 || e1 == e4 || e2 == e3 || e2 == e4 || e3 == e4);
}

int unique_elems(int e1, int e2, int e3, int e4, int r)
{
	return !(e1 == r || e2 == r || e3 == r || e4 == r);
}

int magic_row(int e1, int e2, int e3, int e4)
{
	return ((e1 + e2 + e3 + e4) == 30);
}

int new_row(int e1, int e2, int e3, int e4, int **rows, int count)
{
	int unique;

	// Check if the new row is equal to another, already exisiting row.
	for (unsigned int i = 1; i < count; i++)
	{
		unique = 0;

		unique += unique_elems(e1, e2, e3, e4, rows[i][0]);
		unique += unique_elems(e1, e2, e3, e4, rows[i][1]);
		unique += unique_elems(e1, e2, e3, e4, rows[i][2]);
		unique += unique_elems(e1, e2, e3, e4, rows[i][3]);

		
		// A row is identical to the elements.
		if (unique == 0)
			return 0;		// It's not a new row.
	}

	return 1;
}