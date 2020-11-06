#include "circle.h"

Circle::Circle(const Point& center, double r):
	Ellipse(center, center, 2 * r)
{}

Circle::Circle(const Circle& other):
	Ellipse(other.c, other.c, 2 * other.a)
{}

Circle& Circle::operator=(const Circle& other) {
	if (this == &other)	
		return *this;

	c = f1 = f2 = other.c;
	a = b = other.a;
	return *this;
}

double Circle::radius() const {
	return a;
}

std::ostream& operator<<(std::ostream& out, const Circle& c) {
	out << c.c << " " << c.a << std::endl;
	return out;
}