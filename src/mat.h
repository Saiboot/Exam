#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdlib.h>

#define MAT4x4 16	// 4x4 Matrix - elements


/* Any size matrix type */
typedef struct
{
	char *id;
	int **data;
	int rows;
	int cols;
} mat_t;

/* -=- Any size Matrix -=- */

/*	print_mat:
 *	print a matrix to the console
 *	return: nothing.
 */
void print_mat(const mat_t *matrix);


/* -=- 4x4 Matrix -=- */

/*	init_mat4:
 *	initialize a 4x4 matrix
 *	return: a pointer to the newly created matrix.
 */
mat_t *init_mat4(const int rows, const int columns, const char *name);

/*	is_valid_mat4:
 *	checks whether or not a marrix is valid
 *	a matrix is valid if it only contains unique values
 *	return: 1/0.
 */
int is_valid_mat4(const mat_t *matrix);

/*	is_magic_mat4:
*	checks whether or not a marrix is magical
*	also calls is_valid_mat4 since only valid matrices can be magical
*	a matrix is magical if all the rows and cross-rows are equal when their elements are added together
*	return: 1/0.
*/
int is_magic_mat4(const mat_t *matrix);

/*	free_mat4:
 *	Deallocate a 4x4 matrix from memory
 *	return: nothing.
 */
void free_mat4(mat_t *matrix);

#endif // !_MATRIX_H
