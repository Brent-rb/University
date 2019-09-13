#include "matrix.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>

using namespace std;

int main(int argc, char const *argv[])
{
	Matrix matrix(5, 3);
	Matrix matrix2(5, 3);
	matrix.random();
	matrix2.random();
	cin >> matrix;
	cout << matrix;
	return 0;
}

Matrix::Matrix() {
	matrix = NULL;
}

Matrix::Matrix(int const & rows, int const & columns) {
	matrix = NULL;
	makeMatrix(rows, columns);
}

Matrix::Matrix(int const & dimensions) {
	matrix = NULL;
	makeMatrix(dimensions, dimensions);
}

Matrix::Matrix(Matrix const & matrix) {
	this->matrix = NULL;
	makeMatrix(matrix.rows, matrix.columns);

	for(int i = 0; i < matrix.rows; i++)
		for(int j = 0; j < matrix.columns; j++)
			this->matrix[i][j] = matrix.matrix[i][j];
}

Matrix::~Matrix() {
	deleteMatrix();
}

void Matrix::makeMatrix(int const & rows, int const & columns) {
	deleteMatrix();
	this->rows = rows;
	this->columns = columns;

	matrix = new double*[rows];
	for(int i = 0; i < rows; i++) 
		matrix[i] = new double[columns];

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++) 
			matrix[i][j] = 0;
}

void Matrix::deleteMatrix() {
	if(matrix == NULL)
		return;
	for(int i = 0; i < rows; i++)
		delete[] this->matrix[i];

	delete[] this->matrix;
}

void Matrix::random() {
	srand(time(NULL));
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < columns; j++) {
			matrix[i][j] = (double)((double)(rand() % 10000) / 100.00);
		}
	}
}

ostream& operator<<(ostream& os, const Matrix & m1) {
	
	os.precision(5);
	os.setf( std::ios::fixed, std:: ios::floatfield ); 
	for(int i = 0; i < m1.rows; i++) {
		for(int j = 0; j < m1.columns; j++) {
			os.width(10);
			os << m1[i][j] << " ";
		}
		os << "\n";
	}

	return os;
}

std::istream& operator>>(std::istream & is, Matrix & matrix) {
	char buffer[512];
	bool found = false;
	int i = 0;
	int rows, columns;
	char* token;
	double number;

	do {
		is >> buffer;
		for(i = 0; i < strlen(buffer) && buffer[i] != 'x'; i++);
		if(i != strlen(buffer))
			found = true;
	} while(!found);
	

	buffer[i] = '\0';
	rows = atoi(buffer);
	strcpy(buffer, buffer + i + 1);
	columns = atoi(buffer);
	matrix.makeMatrix(rows, columns);

	for(rows = 0; rows < matrix.rows; rows++) {
		for(columns = 0; columns < matrix.columns; columns++) {
			is >> matrix.matrix[rows][columns];
		}
	}

	return is;
}

Matrix Matrix::operator+(Matrix & matrix) {
	if(matrix.rows != this->rows || matrix.columns != this->columns) {
		Matrix empty(1);
		return empty;
	}

	Matrix cpy(*this);
	for(int i = 0; i < this->rows; i++)
		for(int j = 0; j < this->columns; j++)
			cpy.matrix[i][j] += matrix.matrix[i][j];


	return cpy;

}
void Matrix::operator+=(Matrix & matrix) {
	if(matrix.rows != this->rows || matrix.columns != this->columns) {
		Matrix empty(1);
		return;
	}

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			this->matrix[i][j] += matrix.matrix[i][j];
}

bool Matrix::operator==(Matrix & matrix) {
	if(matrix.rows != this->rows || matrix.columns != this->columns)
		return false;

	for(int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++) 
			if(this->matrix[i][j] != matrix.matrix[i][j])
				return false;

	return true;
}

bool Matrix::operator!=(Matrix & matrix) {
	return (!(*this == matrix));
}

double* Matrix::operator[](int row) {
	return matrix[row];
}
const double* Matrix::operator[](int row) const {
	return matrix[row];
}