#include "square.h"

Square::Square(const Point& a, const Point& b): 
	Rectangle(a, b, 1) 
{}

Square::Square(const Square& other): 
	Rectangle(other.vert[1], other.vert[3], 1) 
{}

Square& Square::operator=(const Square& other) {
	if (this == &other)
		return *this;

	vert = other.vert;
	return *this;
}

Circle Square::circumscribedCircle() const {
	double r = dist(vert[0], vert[2]) / 2;
	return Circle(center(), r); 
}

Circle Square::inscribedCircle() const {
	double r = dist(vert[0], vert[1]) / 2;
	return Circle(center(), r); 
}