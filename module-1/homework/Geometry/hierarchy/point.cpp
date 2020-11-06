#include "line.h"
#include "point.h"

Point::Point(double _x, double _y): x(_x), y(_y) {}

Point::Point(const Point& p): x(p.x), y(p.y) {}

Point& Point::operator=(const Point& p) {
	if (this == &p)
		return *this;

	x = p.x;
	y = p.y;
	return *this;
}

double Point::len() const {
	return sqrt(x * x + y * y);
}

Point Point::rotate(double ang) {
	double new_x = x * cos(ang) - y * sin(ang);
	double new_y = x * sin(ang) + y * cos(ang);
	return Point(new_x, new_y);
}

bool Point::onSegment(const Point& a, const Point& b) const {
	Line l(a, b);
	bool onSeg = (l.dist(*this) < eps);
	
	onSeg &= (std::min(a.x, b.x) + eps < this->x) &&
			 (std::max(a.x, b.x) > this->x + eps) &&
			 (std::min(a.y, b.y) + eps < this->y) &&
			 (std::max(a.y, b.y) > this->y + eps);
	return onSeg;
}

bool operator==(const Point& a, const Point& b) {
	return (fabs(a.x - b.x) < eps) && (fabs(a.y - b.y) < eps);
}

bool operator!=(const Point& a, const Point& b) {
	return !(a == b);
}

Point operator*(double coef, const Point& p) {
	return Point(coef * p.x, coef * p.y);
}

Point operator*(const Point& p, double coef) {
	return coef * p;
}

double operator*(const Point& a, const Point& b) { /// scalar product
	return a.x * b.x + a.y * b.y;
}

double operator^(const Point& a, const Point& b) { /// cross product
	return a.x * b.y - a.y * b.x;
}

Point operator-(const Point& a, const Point& b) {
	return Point(a.x - b.x, a.y - b.y);
}

Point operator+(const Point& a, const Point& b) {
	return Point(a.x + b.x, a.y + b.y);
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
	out.precision(6);
	out << std::fixed << p.x << " " << p.y;
	return out;
}