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
	Complex con(complex.real, complex.im * -1);
	Complex temp;
	temp.real = this->real;
	temp.im = this->im;

	temp.MultiplyWith(con);
	Complex temp2;
	temp2.real = complex.real;
	temp2.im = complex.im;

	temp2.MultiplyWith(con);


	temp.real /= temp2.real;
	temp.im /= temp2.real;

	this->real = temp.real;
	this->im = temp.im;
}

int main() {
	Complex c1;

	cin >> c1;
	cout << c1 << "\n";
	return 0;
}

Complex Complex::operator+(Complex & c1) {
	Complex newC;
	newC.real = this->real + c1.real;
	newC.im = this->im + c1.im;

	return newC;
}

Complex Complex::operator-(Complex & c1) {
	Complex newC;
	newC.real = this->real - c1.real;
	newC.im = this->im - c1.im;

	return newC;
}

Complex Complex::operator*(Complex & c1) {
	Complex newC;

	newC.real += ((this->real * c1.real) - (this->im * c1.im));
	newC.im += ((this->real * c1.im) + (this->im * c1.real));

	return newC;
}

Complex & Complex::operator=(Complex & c1) {
	this->real = c1.real;
	this->im = c1.im;

	return *this;
}

Complex & Complex::operator=(Complex c1) {
	this->real = c1.real;
	this->im = c1.im;

	return *this;
}

Complex::operator Complex() {
	return *this;
}

Complex Complex::operator*(int number) {
	Complex newC;
	newC.real = this->real * number;
	newC.im = this->im * number;

	return newC;
}

Complex operator*(int number, Complex & c1) {
	Complex newC;
	newC.real = c1.real * number;
	newC.im = c1.im * number;

	return newC;
}

Complex Complex::operator/(Complex & c1) {
	Complex newC;
	Complex con(c1.real, c1.im * -1);
	Complex temp;
	temp.real = this->real;
	temp.im = this->im;

	temp.MultiplyWith(con);
	Complex temp2;
	temp2.real = c1.real;
	temp2.im = c1.im;

	temp2.MultiplyWith(con);


	temp.real /= temp2.real;
	temp.im /= temp2.real;

	newC.real = temp.real;
	newC.im = temp.im;

	return newC;
}

void Complex::operator+=(Complex & c1) {
	this->AddTo(c1);
}

void Complex::operator-=(Complex & c1) {
	this->SubtractFrom(c1);
}

void Complex::operator*=(Complex & c1) {
	this->MultiplyWith(c1);
}

void Complex::operator/=(Complex & c1) {
	this->DivideBy(c1);
}

bool Complex::operator==(Complex & c1) {
	if(this->real == c1.real)
		return true;
	else
		return false;
}

bool Complex::operator<=(Complex & c1) {
	if(this->real <= c1.real)
		return true;
	else
		return false;
}

bool Complex::operator>=(Complex & c1) {
	if(this->real >= c1.real)
		return true;
	else
		return false;
}

bool Complex::operator!=(Complex & c1) {
	if(this->real != c1.real)
		return true;
	else
		return false;
}




ostream& operator<<(ostream& os, const Complex & c1) {
  os << c1.real << (c1.im < 0 ? " - ": " + ") << (c1.im < 0 ? c1.im * -1: c1.im) << "i";
  return os;
}
istream& operator>>(istream& is, Complex & c1) {
  cout << "Give real: ";
  is >> c1.real;
  cout << "Give im: ";
  is >> c1.im;
  return is;
}

