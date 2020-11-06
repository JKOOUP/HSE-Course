#include "ellipse.h"

Ellipse::Ellipse(const Point& p1, const Point& p2, double r) {
	c = Point(0.5 * (p1.x + p2.x), 0.5 * (p1.y + p2.y));
	f1 = p1;
	f2 = p2;
	
	a = r / 2;
	double d = dist(f1, c);
	b = sqrt(r * r / 4 - d * d);
}
	
Ellipse::Ellipse(const Ellipse& other):
	c(other.c),
	f1(other.f1),
	f2(other.f2),
	a(other.a),
	b(other.b)
{}

Ellipse& Ellipse::operator=(const Ellipse& other) {
	if (this == &other)
		return *this;

	a = other.a;
	b = other.b;
	f1 = other.f1;
	f2 = other.f2;
	c = other.c;
	return *this;
}

std::pair<Point, Point> Ellipse::focuses() const {
	return std::make_pair(f1, f2);
}

std::pair<Line, Line> Ellipse::directrices() const {
	Line axis(f1, f2);
	Point dir_vec(-axis.b, axis.a);

	dir_vec = (a / eccentricity() / dir_vec.len()) * dir_vec;

	Point a1 = c + dir_vec;
	Point b1 = c - dir_vec;

	Point a2 = a1 + Point(axis.a, axis.b);
	Point b2 = b1 + Point(axis.a, axis.b);	

	return std::make_pair(Line(a1, a2), Line(b1, b2));
}

double Ellipse::eccentricity() const {
	double focus_dist = dist(f1, f2);
	return focus_dist / (2 * a);
}

Point Ellipse::center() const {
	return c;
}

bool Ellipse::operator==(const Shape& other) {
	const Ellipse* ptr = dynamic_cast<const Ellipse*>(&other);
	if (ptr == nullptr)
		return false;

	return (((f1 == ptr->f1) && (f2 == ptr->f2)) ||
			((f2 == ptr->f1) && (f1 == ptr->f2))) &&
			(a == ptr->a);
}

bool Ellipse::isCongruentTo(const Shape& other) {
	const Ellipse* ptr = dynamic_cast<const Ellipse*>(&other);
	if (ptr == nullptr)
		return false;
	
	double focus_dist1 = dist(f1, f2);
	double focus_dist2 = dist(ptr->f1, ptr->f2);

	return (fabs(focus_dist1 - focus_dist2) < eps && 
			fabs(a - ptr->a) < eps);
}

bool Ellipse::isSimilarTo(const Shape& other) {
	const Ellipse* ptr = dynamic_cast<const Ellipse*>(&other);
	if (ptr == nullptr)
		return false;

	double focus_dist1 = dist(f1, f2);
	double focus_dist2 = dist(ptr->f1, ptr->f2);

	return (fabs(focus_dist1 * ptr->a - focus_dist2 * a) < eps);	
}

double Ellipse::perimeter() {
	return 4 * (pi * a * b + (a - b) * (a - b)) / (a + b);
}

double Ellipse::area() {
	return pi * a * b;
}

bool Ellipse::containsPoint(const Point & p) {
	double d1 = dist(p, f1);
	double d2 = dist(p, f2);
	return (d1 + d2 <= 2 * a);
}

void Ellipse::rotate(const Point& center, double angle) {
	angle = pi * angle / 180;
	f1 = (f1 - center).rotate(angle) + center;
	f2 = (f2 - center).rotate(angle) + center;
	c = (c - center).rotate(angle) + center;
}

void Ellipse::reflex(const Point& center) {
	f1 = 2 * (center - f1) + f1;
	f2 = 2 * (center - f2) + f2;
	c = 2 * (center - c) + c;
}

void Ellipse::reflex(const Line& axis) {
	double len_f1 = axis.dist(f1);
	double len_f2 = axis.dist(f2);
	double len_c = axis.dist(c);

	Point norm(axis.a, axis.b);

	Point mvf1 = (len_f1 / norm.len()) * norm;
	if (axis.dist(f1 + mvf1) > eps)
		mvf1 = (-1) * mvf1;

	Point mvf2 = (len_f2 / norm.len()) * norm;
	if (axis.dist(f2 + mvf2) > eps)
		mvf2 = (-1) * mvf2;

	Point mvc = (len_c / norm.len()) * norm;
	if (axis.dist(c + mvc) > eps)
		mvc = (-1) * mvc;

	f1 = 2 * mvf1 + f1;
	f2 = 2 * mvf2 + f2;
	c = 2 * c + c;
}

void Ellipse::scale(const Point& center, double coef) {
	f1 = coef * (f1 - center) + center;
	f2 = coef * (f2 - center) + center;
	c = coef * (c - center) + center;

	a *= coef;
	b *= coef;
}

std::ostream& operator<<(std::ostream& out, const Ellipse& e) {
	out << e.f1 << " " << e.f2 << " " << e.b;
	return out; 
}