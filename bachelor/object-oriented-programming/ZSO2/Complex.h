#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

using namespace std;

class Complex {
public:
	Complex(int real = 0, int im = 0);
	Complex(Complex& complex);
	void SetReal(int real) {this->real = real;}
	void SetIm(int im) {this->im = im;}
	int GetReal() const {return this->real;}
	int GetIm() const{return this->im;}
	void SchrijfUit() const {(this->im < 0 ? cout << this->real << " - " << this->im * -1 << "i\n": cout << this->real << " + " << this->im << "i\n");}
	void AddTo(const Complex& complex) {this->real += complex.GetReal(); this->im += complex.GetIm();}
	void SubtractFrom(const Complex& complex) {this->real -= complex.GetReal(); this->im -= complex.GetIm();}
	void MultiplyWith(const Complex& complex);
	void DivideBy(const Complex& complex);
private:
	int real;
	int im;
};


#endif
