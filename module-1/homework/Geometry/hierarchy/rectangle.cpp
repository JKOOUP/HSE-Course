#include "rectangle.h"

Rectangle::Rectangle(const Point& _b, const Point& _d, double k) {
	Point b = _b;
	Point d = _d;

	double ang = atan(k);	
	double diag_len = (d - b).len(); 
	double ab_len = diag_len * cos(ang);
	double bc_len = diag_len * sin(ang);

	Point a = (ab_len / diag_len) * (d - b).rotate(ang) + b;
	Point c = (bc_len / diag_len) * (d - b).rotate(ang - pi / 2) + b;
	
	this->vert = {a, b, c, d};
}

Rectangle::Rectangle(const Rectangle& other): 
	Polygon(other) 
{}

Rectangle& Rectangle::operator=(const Rectangle& other) {
	if (this == &other)
		return *this;

	this->vert = other.vert;
	return *this;
}

Point Rectangle::center() const {
	return Point(0.25 * (vert[0].x + vert[1].x + vert[2].x + vert[3].x),
	 			 0.25 * (vert[0].y + vert[1].y + vert[2].y + vert[3].y));
}

std::pair <Line, Line> Rectangle::diagonals() const {
	Line l1 = Line(vert[0], vert[2]);
	Line l2 = Line(vert[1], vert[3]);
	return std::make_pair(l1, l2);
}