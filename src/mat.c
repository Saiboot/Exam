#include "mat.h"

#include <stdio.h>
#include "hex.h"

mat_t *init_mat4(int rows, int columns, const char *name)
{
	mat_t *matrix = malloc(sizeof(mat_t));
	matrix->rows = rows;
	matrix->cols = columns;
	matrix->data = (int **)malloc(rows * sizeof(int *));

	for (int i = 0; i < rows; i++)
		matrix->data[i] = (int *)malloc(columns * sizeof(int));

	for (size_t i = 0; i < matrix->rows; i++)
	{
		for (size_t j = 0; j < matrix->cols; j++)
		{
			matrix->data[i][j] = 20;
		}
	}

	matrix->id = name;
	return matrix;
}

void free_mat4(mat_t *matrix)
{
	for (int i = 0; i < matrix->rows; i++)
		free(matrix->data[i]);
	free(matrix->data);
}

void print_mat(mat_t *matrix)
{
	printf("\n");

	printf("   0  1  2  3\n");
	for (size_t r = 0; r < matrix->rows; r++)
	{
		printf("%d ", r);
		for (size_t c = 0; c < matrix->cols; c++)
		{
			if (matrix->data[r][c] != 20)
				printf("[%c]", getHex(matrix->data[r][c]));
			else
				printf("[ ]");
		}
		printf("\n");
	}

	printf("\n");
}

int is_valid_mat4(mat_t *matrix)
{
	int sum = 0;
	for (size_t i = 0; i < matrix->rows; i++)
	{
		for (size_t j = 0; j < matrix->cols; j++)
		{
			sum += matrix->data[i][j];
		}
	}

	if (sum == 120)
		return 1;

	return 0;
}

int is_magic_mat(mat_t *matrix)
{
	if (!is_valid_mat4(matrix))
		return 0;

	int magic = 1;

	int magic_row = 0;
	int magic_column = 0;

	for (size_t i = 0; i < matrix->rows; i++)
	{
		for (size_t j = 0; j < matrix->cols; j++)
		{			
			magic_row    += matrix->data[i][j];
			magic_column += matrix->data[j][i];
		}

		if (magic_row + magic_column != 60)
			magic = 0;

		magic_row = 0;
		magic_column = 0;
	}

	return magic;
}