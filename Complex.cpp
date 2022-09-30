#include "Complex.h"

Complex::Complex(double r, double i) {
    real = r;
    imag = i;
}

double Complex::getReal() {
    return this->real;
}

double Complex::getImag() {
    return this->imag;
}

void Complex::setReal(double real) {
    this->real = real;
}

void Complex::setImag(double imag) {
    this->imag = imag;
}

Complex  Complex :: operator+(const Complex& op2) const {
    Complex result;
    result.real = op2.real + real;
    result.imag = op2.imag + imag;
    return result;
}

Complex  Complex :: operator-(const Complex& op2) const {
    Complex result;
    result.real = real - op2.real;
    result.imag = imag - op2.imag;
    return result;
}

Complex  Complex :: operator*(const Complex& op2) const {
    Complex result;
    result.real = real * op2.real - imag * op2.imag;
    result.imag = imag * op2.real + real * op2.imag;
    return result;
}
