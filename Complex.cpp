#include "Complex.hpp"

Complex::Complex() : imag(0), real(0)
{
}

Complex::Complex(const Complex& a) : imag(a.imag), real(a.real)
{
}

Complex::Complex(double a, double b) : imag(a), real(b)
{
}

double& Complex::operator[](const char* c)
{
	if ((strcmp("real", c) == 0))
	{
		return this->real;
	}
	else if ((strcmp("imag", c) == 0))
	{
		return this->imag;
	}
	exit(1);
}

Complex::~Complex()
{
}

const Complex operator*(const Complex& a, const Complex& b)
{
	Complex result;
	result.real = (a.real * b.real) - (a.imag * b.imag);
	result.imag = (a.real * b.imag) + (a.imag * b.real);
	return result;
}

const Complex operator+(const Complex& a, const Complex& b)
{
	Complex result;
	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return result;
}

double getMagnitudeSquared(const Complex& a) 
{
	double result = pow(a.imag, 2) + pow(a.real, 2);
	return result;
}

