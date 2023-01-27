#include <iostream>
#include <string>
#include <fstream>
#include "Pixel.hpp"
#include "Complex.hpp"
using namespace std;

class Fractal
{
private:
	unsigned int rows;
	unsigned int cols;
	unsigned int maxiter;

	Pixel** grid;
	char type;

	void makeJuliaFractal();
	void makeMandelbrotFractal();

	unsigned int determinePixelColour(Complex&, Complex&);
	Pixel convertToPixel(unsigned int);
public:
	Fractal();
	Fractal(const Fractal&);
	Fractal(Fractal&&);
	Fractal(unsigned int, unsigned int, char);
	const Fractal& operator=(const Fractal&);
	Fractal& operator=(Fractal&&);

	friend void saveToPPM(Fractal&, const char*);


	~Fractal();

};
