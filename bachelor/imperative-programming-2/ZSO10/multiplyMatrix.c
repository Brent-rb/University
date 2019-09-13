#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void multiply(int**, int**, int**, int, int);

int main(int argc, char const *argv[])
{
	int** matrix1 = NULL;
	int** matrix2 = NULL;
	int** result = NULL;
	int row, column;
	int i, j;


	printf("Give the dimension (row column).\n");
	scanf("%d %d", &row, &column);

	matrix1 = (int**) malloc(sizeof(int*) * row);
	matrix2 = (int**) malloc(sizeof(int*) * row);
	result = (int**) malloc(sizeof(int*) * row);
	

	for(i = 0; i < column; i++) {
		matrix1[i] = (int*) malloc(sizeof(int) * column);
		matrix2[i] = (int*) malloc(sizeof(int) * column);
		result[i] = (int*) malloc(sizeof(int) * column);
	}
	srand(time(NULL));
	for(i = 0; i < row; i++) {
		for(j = 0; j < column; j++) {
			
			matrix1[i][j] = (rand() % 100);
			matrix2[i][j] = (rand() % 100);
		}
	}

	for(i = 0; i < row; i++) {
		for(j = 0; j < column; j++) {
			printf("Matrix1[%d][%d]: %d\n", i, j, matrix1[i][j]);
			printf("Matrix2[%d][%d]: %d\n", i, j, matrix2[i][j]);
		}
	}

	multiply(matrix1, matrix2, result, row, column);

	for(i = 0; i < row; i++) {
		for(j = 0; j < column; j++) {
			printf("Result[%d][%d]: %d\n", i, j, result[i][j]);
		}
	}

	for(i = 0; i < row; i++) {
		free(matrix1[i]);
		free(matrix2[i]);
		free(result[i]);
	}

	free(matrix1);
	free(matrix2);
	free(result);


	return 0;
}

void multiply(int** matrix1, int** matrix2, int** result, int row, int column) {
	int i, j, k, l;
	int som;

	for(i = 0; i < row; i++) {
		for(j = 0; j < column; j++) {
			som = 0;
			for(k = 0; k < row; k++) {
				som += matrix1[i][k] * matrix2[k][j];
			}
			result[i][j] = som;
			printf("%d\n", result[i][j]);
		}
		
	}
}