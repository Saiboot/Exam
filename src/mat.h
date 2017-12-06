#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdlib.h>

#define MAT4x4 16

typedef struct
{
	char *id;
	int **data;
	int rows;
	int cols;
} mat_t;

/* Any Matrix */
void print_mat(mat_t *matrix);

int is_magic_mat(mat_t *matrix);


/* 4x4 Matrix */
mat_t *init_mat4(int rows, int columns, const char *name);

int is_valid_mat4(mat_t *matrix);

void free_mat4(mat_t *matrix);

#endif // !_MATRIX_H
