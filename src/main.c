#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <time.h>

#include "mat.h"
#include "IO\fio.h"

#include "../PCLIBS/random.h"

#define NAME_MAX 20


int main()
{

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
		puts("(4) Exit.");

		if(hex_mat)
			printf("::|Current Matrix: %s\n\n", hex_mat->id);

		printf(">> ");
		scanf("%d", &opt);
		getchar();


		switch (opt)
		{
		case 1:
			printf("Name your new matrix: ");
			scanf("%s", name);

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
		case 2:
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
			case 1:
				printf("Matrix name: ");
				scanf("%s", name);
				getchar();

				hex_mat = load_matrix(file_path, name);
				break;
			case 2:
				printf("Line number: ");
				scanf("%d", &line);
				getchar();

				if(line)
					hex_mat = load_matrix_by_line(file_path, line);

				break;
			case 3:
				break;
			default:
				break;
			}
			
			if (opt < 3) {

				system("cls");

				printf("Loaded Matrix: %s \n", hex_mat->id);
				print_mat(hex_mat);
				printf("Magic [1/0]: [%d]", is_magic_mat(hex_mat));
				getchar();

			}
			break;
		case 3:

			system("cls");
			printf("Loading magic matrix...\n");

			int ln = 0;
			ln = rand() % 10 + 1;
			
			/* load a predefined matrix */
			hex_mat = load_matrix_by_line("hexkvadrater.txt", ln);

			/* make sure we loaded a matirx, it's magic and it's a valid matrix (validness checked within is_magic_mat() func). */
			if (hex_mat && is_magic_mat(hex_mat)) {
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

			if (is_magic_mat(hex_mat))
				printf("It's magical!!\n");

			break;
		case 4:
			exit(EXIT_SUCCESS);
		default:
			printf("Invalid option!\n");
			getchar();
			getchar();
		}
	}

	getchar();
	return 0;
}

int check_mat(mat_t *matrix, int value)
{
	for (size_t i = 0; i < matrix->rows; i++)
	{
		for (size_t j = 0; j < matrix->cols; j++)
		{
			if (matrix->data[i][j] == value)
				return 1;
		}
	}

	return 0;
}

