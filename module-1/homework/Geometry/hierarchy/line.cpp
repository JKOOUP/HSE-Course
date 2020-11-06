#include "line.h"

Line::Line(const Point& p1, const Point& p2) {
	a = p2.y - p1.y;
	b = p1.x - p2.x;
	c = p1.y * p2.x - p2.y * p1.x;

	double len = sqrt(a * a + b * b);
	a /= len;
	b /= len;
	c /= len;
}

Line::Line(const Line& other): 
	a(other.a), 
	b(other.b), 
	c(other.c) 
{}

Line& Line::operator=(const Line& other) {
	if (this == &other)
		return *this;

	a = other.a;
	b = other.b;
	c = other.c;
	return *this;
}

double Line::dist(const Point& p) const {
	double len = sqrt(a * a + b * b);
	return fabs(a * p.x + b * p.y + c) / len; 
}

bool operator==(const Line& l1, const Line& l2) {
	return (fabs(l1.a - l2.a) < eps) &&
		   (fabs(l1.b - l2.b) < eps) &&
		   (fabs(l1.c - l2.c) < eps);	
}

bool operator!=(const Line& l1, const Line& l2) {
	return !(l1 == l2);
}