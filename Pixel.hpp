#include <iostream>
#include <string>
using namespace std;

class Pixel
{
private:
	unsigned int blue;
	unsigned int green;
	unsigned int red;
public:
	Pixel();
	Pixel(const Pixel&);
	Pixel(unsigned int, unsigned int, unsigned int);

	const unsigned int& operator[](const char*) const;

	friend ostream& operator<<(ostream&, const Pixel&);

	~Pixel();
};