#include "Fractal.hpp"

Fractal::Fractal() : cols(0), grid(nullptr), rows(0), maxiter(512),type(' ')
{
	cout << "> Default constructor called..." << endl;
}

Fractal::Fractal(unsigned int c, unsigned int r, char t) : cols(c), rows(r), type(t), maxiter(512)
{
	cout << "> 3-arg constructor called..." << endl;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	if (type == 'm')
	{
		makeMandelbrotFractal();
	}
	else if (type == 'j')
	{
		makeJuliaFractal();
	}
	else
	{
		cout << "Invalid type" << endl;
		exit(1);
	}
}

Fractal::Fractal(const Fractal& f) : rows(f.rows), cols(f.cols), type(f.type), maxiter(512)
{
	cout << "> Copy constructor called..." << endl;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	if (type == 'm')
	{
		makeMandelbrotFractal();
	}
	else if (type == 'j')
	{
		makeJuliaFractal();
	}
	else
	{
		cout << "Invalid type" << endl;
		exit(1);
	}
}


Fractal::Fractal(Fractal&& temp) : rows(temp.rows), cols(temp.cols), maxiter(temp.maxiter), type(temp.type) {
	cout << "Move constructor called..." << endl;
	grid = temp.grid;
	temp.cols = 0;
	temp.rows = 0;
	temp.type = NULL;
	temp.maxiter = 0;
	temp.grid = nullptr;
}

const Fractal& Fractal::operator=(const Fractal& f)
{
	cout << "> Assignment Operator called..." << endl;
	maxiter = f.maxiter;
	rows = f.rows;
	cols = f.cols;
	type = f.type;
	grid = f.grid;
	grid = new Pixel * [rows];
	for (unsigned int i = 0; i < rows; i++)
	{
		grid[i] = new Pixel[cols];
	}
	for (unsigned int i = 0; i < rows; i++)
	{
		for (unsigned int j = 0; j < rows; j++)
		{
			grid[i][j] = f.grid[i][j];
		}
	}
	return *this;
}

Fractal& Fractal::operator=(Fractal&& pnt)
{
	cout << "> Move assignment operator called..." << endl;
	if (this != &pnt)
	{
		swap(rows, pnt.rows);
		swap(cols, pnt.cols);
		swap(type, pnt.type);
		swap(grid, pnt.grid);
		swap(maxiter, pnt.maxiter);
	}
	pnt.grid = nullptr;
	return *this;
}


Fractal::~Fractal()
{
	cout << "> Destructor called..." << endl;
	for (unsigned int i = 0; i < rows; i++) 
	{
		delete[] grid[i];
	}
	delete[] grid;
}


unsigned int Fractal::determinePixelColour(Complex&Z, Complex& C)
{
	double lengthSquared;
	unsigned int iter = 0;
	while (iter < maxiter)
		{
			iter = iter + 1;
			Z = Z * Z;
			Z = Z + C;
			lengthSquared = getMagnitudeSquared(Z);
			if (lengthSquared > 4.0)
			{
				return iter;
			}
		}
	return maxiter;
}

Pixel Fractal::convertToPixel(unsigned int c)
{
		unsigned int red, green, blue;
		red = (c / 64) % 8;
		green = (c / 8) % 8;
		blue = (c % 8);
		return Pixel(red, green, blue);
}


void Fractal::makeJuliaFractal()
{
	cout << "> Now creating the Julia patterns..." << endl;
	Complex Z;
	Complex C(0.156, -0.8);
	double step_height = 4.0 / (double)rows;
	double step_width = 4.0 / (double)cols;
	for (unsigned int j = 0; j < rows; j++)
	{
		for (unsigned int k = 0; k < cols; k++)
		{

			Z["real"] = ((double)j * step_height) - 2.0;
			Z["imag"] = ((double)k * step_width) - 2.0;
			unsigned int colour = determinePixelColour(Z, C);
			
			grid[j][k] = convertToPixel(colour);
		}
	}
}

void Fractal::makeMandelbrotFractal()
{
	cout << "> Now creating the Mandelbrot patterns..." << endl;
	Complex Z, C;
	double step_height = 4.0 / (double)rows;
	double step_width = 4.0 / (double)cols;
	for (unsigned int j = 0; j < rows; j++)
	{
		for (unsigned int k = 0; k < cols; k++)
		{
			Z["imag"] = 0.0;
			Z["real"] = 0.0;
			C["real"] = ((double)j * step_height) - 2.0;
			C["imag"] = ((double)k * step_width) - 2.0;
			unsigned int colour = determinePixelColour(Z, C);
			grid[j][k] = convertToPixel(colour);
		}

	}
}

void saveToPPM(Fractal& fileIn, const char* newFile)
{
	cout << "> Saving Fractal object to ASCII file..." << endl;
	fstream outputFile(newFile, ios:: out);
	outputFile << "P3" << endl;
	if (fileIn.type == 'm')
	{
		outputFile << "# MandelBrot Fractal" << endl;
	}
	else if (fileIn.type == 'm')
	{
		outputFile << "# Julia Fractal" << endl;
	}

	outputFile << fileIn.cols << " " << fileIn.rows <<endl;
	outputFile << "7" << endl;
	for (unsigned int i = 0; i < fileIn.rows; i++)
	{
		for (unsigned int j = 0; j < fileIn.cols; j++)
		{
			outputFile << fileIn.grid[i][j] << " ";
		}
		outputFile << endl;
	}
	outputFile.close();
	
}