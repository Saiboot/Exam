#ifndef _FIO_H
#define _FIO_H

#include "../../PCLIBS/simpio.h"	// File io
#include "../mat.h"
#include "../hex.h"

#include <string.h>

/*	io_File:
 *	File I/O
 *	- Output: read data from file.
 *	- Input: append data to a file.
 *	return:
 *		- Output: file data address.
 *		- Input: nothing.
 */
char *io_File(const char *file_path, const char *mode, const char *src);

/*	save_matrix:
 *	save a matrix to a file.
 *	return: nothing.
 */
void save_matrix(const mat_t *matrix, const char *path);

/*	load_matrix:
 *	load a matrix from a file by ID/name
 *	return: the loaded matrix address.
 */
mat_t *load_matrix(const char *path, const char *matrixID);

/*	load_matrix_by_line:
 *	load a matrix by file line number
 *	return: the loaded matrix address.
 */
mat_t *load_matrix_by_line(const char *path, int line);

#endif // !_FIO_H
