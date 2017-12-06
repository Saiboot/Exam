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
		//fwrite(src, strlen(src), 1, pFile);



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
	//strcat(mat_str, matrix->id);
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
	//FILE *pfile = fopen(path, "r");

	//char *line;
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

		//line = ReadLine(pfile);
		//token = strtok(line, ":");	// get matrix ID
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

	//fclose(pfile);
	return matrix;
}
