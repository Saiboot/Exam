#ifndef _FIO_H
#define _FIO_H

#include "../../PCLIBS/simpio.h"	// File io
#include "../mat.h"

#include <string.h>

//	
//	Inspect file content
//	@param: file path
//	
//	@return: file content (char *)
//	
char *io_File(const char *file_path, const char *mode, const char *src);

void save_matrix(const mat_t *matrix, const char *path);

mat_t *load_matrix(const char *path, const char *matrixID);

#endif // !_FIO_H
