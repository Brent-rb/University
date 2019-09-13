#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix {
public:
	Matrix();
	Matrix(int const & rows, int const & columns);
	Matrix(int const & dimensions);
	Matrix(Matrix const & matrix);
	~Matrix();
	void printMatrix();
	void random();

	Matrix operator+(Matrix & matrix);
	void operator+=(Matrix & matrix);
	bool operator==(Matrix & matrix);
	bool operator!=(Matrix & matrix);
	double* operator[](int row);
	const double* operator[](int row) const;

	friend std::ostream& operator<<(std::ostream & os, const Matrix & m1);
	friend std::istream& operator>>(std::istream & is, Matrix & matrix);

private:
	void makeMatrix(int const & rows, int const & columns);
	void deleteMatrix();
	double** matrix;
	unsigned int rows;
	unsigned int columns;
};

#endif