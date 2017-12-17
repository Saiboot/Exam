#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <time.h>

#include "row.h"

#include "mat.h"
#include "IO\fio.h"

#include "../PCLIBS/random.h"

#define NAME_MAX 20


int main()
{
	int **rows;
	int opt = 0;

	mat_t *hex_mat = init_mat4(4, 4, NULL);
	int duplicate = 0;

	char *name = malloc(sizeof(char) * NAME_MAX);
	char *file_path = malloc(sizeof(char) * 25);

	Randomize();

	while (1)
	{
		system("cls");

		/* menu */
		puts(".:|Menu");
		puts("(1) Input new 4x4 Matrix.");
		puts("(2) Load 4x4 Matrix from file.");
		puts("(3) Play Fill in matrix game.");
		puts("(4) Calculate  magic squares & rows.");
		puts("(5) Exit.");

		if(hex_mat)
			printf("::|Current Matrix: %s\n\n", hex_mat->id);

		printf(">> ");
		scanf("%d", &opt);
		getchar();

		/* options */
		switch (opt)
		{
		case 1:	// Input new 4x4 Matrix.
			printf("Name your new matrix: ");
			scanf("%s", name);
			getchar();

			hex_mat->id = name;
			duplicate = 0;

			for (size_t r = 0; r < hex_mat->rows; r++)
			{
				for (size_t c = 0; c < hex_mat->cols; c++)
				{
					int tmp = 0;
					do {
						system("cls");
						printf("Hex -Matrix Table: %s \n", hex_mat->id);

						print_mat(hex_mat);

						if (duplicate && tmp != 20)
							printf("Error: value duplicate!\n");

						printf("[%d][%d]: ", r, c);
						scanf("%d", &tmp);
						getchar();

						duplicate = check_mat(hex_mat, tmp);

					} while (!(tmp <= 15 && tmp >= 0) || duplicate);

					hex_mat->data[r][c] = tmp;
				}
			}

			//:...
			system("cls");
			printf("Hex -Matrix Table: %s \n", hex_mat->id);
			print_mat(hex_mat);

			puts("Do you wish to save the matrix? 1/0");
			scanf("%d", &opt);
			getchar();

			if (opt) {
				printf("File path: ");
				scanf("%s", file_path);
				getchar();

				save_matrix(hex_mat, file_path);
				printf("Saved matrix.");
				getchar();
			}

			break;
		case 2: // Load 4x4 Matrix from file.
			system("cls");
			puts("(1) Load by matrix name. \t(matrices.txt) ");
			puts("(2) Load by line number. \t(hexkvadrater.txt) ");
			puts("(3) Return to main menu.");

			puts("\n NOTE: Some files needs to be loaded by name, some by line number.");

			printf("\n>> ");
			scanf("%d", &opt);
			getchar();

			printf("File path: ");
			scanf("%s", file_path);
			getchar();

			int line;

			switch (opt)
			{
			case 1: // Load by name.
				printf("Matrix name: ");
				scanf("%s", name);
				getchar();

				hex_mat = load_matrix(file_path, name);
				break;
			case 2: // Load by line number.
				printf("Line number: ");
				scanf("%d", &line);
				getchar();

				if(line)
					hex_mat = load_matrix_by_line(file_path, line);

				break;
			case 3: // Return to main menu.
				break;
			default:
				break;
			}
			
			if (opt < 3) {

				system("cls");

				printf("Loaded Matrix: %s \n", hex_mat->id);
				print_mat(hex_mat);
				printf("Magic [1/0]: [%d]", is_magic_mat4(hex_mat));
				getchar();

			}
			break;
		case 3: // Play Fill in matrix game.

			system("cls");
			printf("Loading magic matrix...\n");

			int ln = 0;
			ln = rand() % 10 + 1;
			
			/* load a predefined matrix */
			hex_mat = load_matrix_by_line("hexkvadrater.txt", ln);

			/* make sure we loaded a matirx, it's magic and it's a valid matrix (validness checked within is_magic_mat() func). */
			if (hex_mat && is_magic_mat4(hex_mat)) {
				printf("Load successful!\n");
				printf("Start game?");
				getchar();
			} else {

				printf("Make sure matrices.txt is located under the solution directory!");
				getchar();
				break;
			}
				

			int difficulty = RandomInteger(1, 8);

			for (size_t i = 0; i < difficulty; i++)
				hex_mat->data[RandomInteger(0, 3)][RandomInteger(0, 3)] = 20;

			int r, c, val;
			duplicate = 0;
			while (!is_valid_mat4(hex_mat))
			{
				do {

					system("cls");
					printf("Hex -Matrix Table: %s \n", hex_mat->id);

					print_mat(hex_mat);

					if (duplicate && val != 20)
						printf("Error: value duplicate!\n");

					printf("Edit (row column): ");
					scanf("%d %d", &r, &c);
					getchar();

					if (hex_mat->data[r][c] != 20) {
						printf("You can only edit empty slots!");
						getchar();
						continue;
					}


					printf("[%d][%d]: ", r, c);
					scanf("%d", &val);
					getchar();

					duplicate = check_mat(hex_mat, val);

				} while (!(val <= 15 && val >= 0) || duplicate);

				hex_mat->data[r][c] = val;

			}

			system("cls");
			print_mat(hex_mat);

			if (is_magic_mat4(hex_mat))
				printf("It's magical!!\n");

			break;
		case 4:

			rows = malloc(sizeof(int *));
			rows[0] = malloc(sizeof(int) * ROW_ELEMS);

			// First row is a trash row.
			for (size_t i = 0; i < ROW_ELEMS; i++)
				rows[0][i] = 55;

			int rows_cnt = 1;
			int valid_row_cnt = 0;
			int magic_cnt = 0;

			for (size_t e1 = 0; e1 < MAT4x4; e1++) {
				for (size_t e2 = 0; e2 < MAT4x4; e2++) {
					for (size_t e3 = 0; e3 < MAT4x4; e3++) {
						for (size_t e4 = 0; e4 < MAT4x4; e4++) {

							if (valid_row(e1, e2, e3, e4)) {
								valid_row_cnt++;

								if (magic_row(e1, e2, e3, e4)) {
									magic_cnt++;

									if (new_row(e1, e2, e3, e4, rows, rows_cnt)) {

										rows_cnt++;

										rows = realloc(rows, sizeof(int *) * rows_cnt);
										rows[(rows_cnt - 1)] = malloc(sizeof(int) * ROW_ELEMS);

										rows[(rows_cnt - 1)][0] = e1;
										rows[(rows_cnt - 1)][1] = e2;
										rows[(rows_cnt - 1)][2] = e3;
										rows[(rows_cnt - 1)][3] = e4;

										printf("Inserted >> [%d] { %d, %d, %d, %d }\n", (rows_cnt - 1), e1, e2, e3, e4);
									}
								}
							}
						}
					}
				}
			}

			printf("\nGenerated:\n");
			printf("valid rows count: %d\n", valid_row_cnt);
			printf("magic rows count: %d\n", magic_cnt);
			printf("Unique rows: %d\n", rows_cnt-1);
			getchar();

			printf("Calculating squares...\n");
			register int squares = 0;

			for (size_t r1 = 1; r1 < rows_cnt; r1++)
				for (size_t r2 = 1; r2 < rows_cnt; r2++) {

					if (!unique_row(rows[r1], rows[r2]))
						continue;

					for (size_t r3 = 1; r3 < rows_cnt; r3++) {

						if (!unique_row(rows[r1], rows[r3]))
							continue;

						if (!unique_row(rows[r2], rows[r3]))
							continue;

						for (size_t r4 = 1; r4 < rows_cnt; r4++)
						{

							if (!unique_row(rows[r1], rows[r4]))
								continue;

							if (!unique_row(rows[r2], rows[r4]))
								continue;

							if (!unique_row(rows[r3], rows[r4]))
								continue;

							squares++;


						}

					}
				}

			printf("DONE, found %d squares!\n", squares);
			getchar();

		case 5:
			exit(EXIT_SUCCESS);
		default:
			printf("Invalid option! ");
			getchar();
		}
	}

	getchar();
	return 0;
}
