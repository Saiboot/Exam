#include "fio.h"

char *io_File(const char *file_path, const char *mode, const char *src) {

	/* open file steam */
	FILE *pFile = fopen(file_path, mode);

	/* make sure we loaded the file */
	if (!pFile) {
		printf("Couldn't locate %s\n", file_path);
		return NULL;
	}
	
	/* Mode: read */
	if (!strcmp(mode, "r")) {

		/* file size */
		fseek(pFile, 0L, SEEK_END);
		long size = ftell(pFile);
		fseek(pFile, 0L, SEEK_SET);
		rewind(pFile);

		if (size < 0)
			printf("File error, size: %d", size);

		/* allocate file buffer - depending on file size */
		char *aBuf = malloc(sizeof(char) * size + 1);
		memset(aBuf, 0, size + 1);

		/* read file content into buffer */
		fread(aBuf, size, 1, pFile);
		if (ferror(pFile))
			return NULL;

		/* null-terminate buffer */
		aBuf[size] = '\0';

		/* close file stream */
		fclose(pFile);

		return aBuf;
	}

	/* Mode: write */
	if (!strcmp(mode, "a"))
		fputs(src, pFile);



	/* close file stream */
	fclose(pFile);

	return NULL;
}

void save_matrix(const mat_t *matrix, const char *path)
{
	char *mat_str = malloc(sizeof(char) * 50);
	char aBuf[20];
	memset(aBuf, 0, 20);

	strcpy(mat_str, matrix->id);
	strcat(mat_str, ":");

	for (size_t r = 0; r < 4; r++)
		for (size_t c = 0; c < 4; c++)
		{
			strcat(mat_str, _itoa(matrix->data[r][c], aBuf, 10));
			strcat(mat_str, " ");
		}

	strcat(mat_str, "\n\0");

	io_File(path, "a", mat_str);
}

mat_t *load_matrix(const char *path, const char *matrixID)
{
	int init = 0;
	mat_t *matrix = init_mat4(4, 4, matrixID);

	char *token = NULL;
	char *aBuf = io_File(path, "r", NULL);

	if (!aBuf)
		return NULL;

	token = strtok(aBuf, ":");	// initiate strtok(..)

	/* Search for matrix ID */
	do {
		/* go to next matrix */
		if (init) {
			strtok(NULL, "\n");
			token = strtok(NULL, ":");
		}
		else if(init && token == NULL)
			return NULL;

		init = 1;
	} while (strcmp(token, matrixID) /*|| line != NULL*/);
	
	init = 0;

	/* found matrix ID */
	if (token) {
		char *data = strtok(NULL, "\n");
		token = strtok(data, " ");

		/* fill in a new matrix */
		for (size_t r = 0; r < 4; r++)
			for (size_t c = 0; c < 4; c++)
			{
				if (init)
					token = strtok(NULL, " ");
				else
					init = 1;
				matrix->data[r][c] = atoi(token);
			}

	} else
		return NULL;

	if(is_valid_mat4(matrix))
		return matrix;

	return NULL;
}

mat_t *load_matrix_by_line(const char *path, int line)
{
	mat_t *matrix = init_mat4(4, 4, "HEXKV");	// name: "HEXKV" since there's no name associated with the matrix.

	FILE *pfile = fopen(path, "r");
	char *data = malloc(32);

	/* aquire matrix by line */
	for (size_t i = 0; i < line; i++)
		data = ReadLine(pfile);

	/* close the file stream since we got the matrix */
	fclose(pfile);

	/* get first character in the matrix */
	data = strtok(data, " ");
	int init = 0;

	/* make sure we got the matrix data */
	if (!data)
		return NULL;

	/* loop through every other character */ //--
	for (size_t r = 0; r < 4; r++)			 // row
		for (size_t c = 0; c < 4; c++)		 // column
		{
			if (init)
				data = strtok(NULL, " ");
			else
				init = 1;
			matrix->data[r][c] = getInt(*(data));	// populate the matrix variable structure.

		}

	if (is_valid_mat4(matrix))
		return matrix;

	return NULL;
}