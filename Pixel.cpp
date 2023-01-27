#include "Pixel.hpp"

Pixel::Pixel() : blue(0), green(0), red(0)
{
}

Pixel::Pixel(const Pixel& a) : blue(a.blue), green(a.green), red(a.red)
{
}

Pixel::Pixel(unsigned int b, unsigned int g, unsigned int r) : blue(r), green(g), red(r)
{
}

const unsigned int& Pixel::operator[](const char* c) const
{
	if (strcmp("blue", c) == 0)
	{
		return this->blue;
	}
	else if (strcmp("green", c) == 0)
	{
		return this->green;
	}
	else if (strcmp("red", c) == 0)
	{
		return this->red;
	}
	exit(1);
}

Pixel::~Pixel()
{
}

ostream& operator<<(ostream& os, const Pixel& p)
{
	os << p["red"] << " " << p["green"] << " " << p["blue"];
	return os;
}
