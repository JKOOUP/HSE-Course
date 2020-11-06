#include "triangle.h"

Triangle::Triangle(const Point& a, const Point& b, const Point& c):
	Polygon({a, b, c}) 
{}

Triangle::Triangle(const Triangle& other):
	Polygon(other.vert)
{}

Triangle& Triangle::operator=(const Triangle& other) {
	vert = other.vert;
	return *this;
}

Circle Triangle::circumscribedCircle() const {
	Point center;
	Point a = vert[0];
	Point b = vert[1];
	Point c = vert[2];

	double slena = a.len() * a.len();
	double slenb = b.len() * b.len();
	double slenc = c.len() * c.len();

	double d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
	center.x = (slena * (b.y - c.y) + slenb * (c.y - a.y) + slenc * (a.y - b.y)) / d;
	center.y = (slena * (c.x - b.x) + slenb * (a.x - c.x) + slenc * (b.x - a.x)) / d;

	double r = dist(center, vert[0]);
	return Circle(center, r);
}

Circle Triangle::inscribedCircle() const {
	double a = (vert[1] - vert[2]).len();
	double b = (vert[0] - vert[2]).len();
	double c = (vert[0] - vert[1]).len();

	Point center = (1 / (a + b + c)) * (a * vert[0] + b * vert[1] + c * vert[2]);
	double r = Line(vert[0], vert[1]).dist(center);

	return Circle(center, r);
}