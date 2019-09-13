#include "Complex.h"
#include <iostream>


Complex::Complex(int real, int im) {
	this->real = real;
	this->im = im;
}

Complex::Complex(Complex& complex) {
	cout << "Copy constructer engaged\n";
	this->real = complex.GetReal();
	this->im = complex.GetIm();
}

void Complex::MultiplyWith(const Complex& complex) {
	int real = 0;
	int im = 0;

	real += ((this->real * complex.GetReal()) - (this->im * complex.GetIm()));
	im += ((this->real * complex.GetIm()) + (this->im * complex.GetReal()));

	this->real = real;
	this->im = im;
}

void Complex::DivideBy(const Complex& complex) {
	int deler = (complex.GetReal() * complex.GetReal()) + (complex.GetIm() * complex.GetIm());
	int real = (this->real * complex.GetReal()) + (this->im * complex.GetIm());
	int im = (this->im * complex.GetReal()) - (this->real * complex.GetIm());
	cout << "Real: " << real << "\n";
	cout << "Im: " << im << "\n";	
	real /= deler;
	im /= deler;

	cout << "Deler: " << deler << "\n";
	cout << "Real: " << real << "\n";
	cout << "Im: " << im << "\n";

	this->real = real;
	this->im = im;
}

int main() {
	Complex c1(5,3);
	Complex c2 = c1;

	c1.SchrijfUit();
	c2.SchrijfUit();
}