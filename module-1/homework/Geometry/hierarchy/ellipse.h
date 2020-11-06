#pragma once
#include "shape.h"

class Ellipse : public Shape {
public:

	Ellipse() = default;

	Ellipse(const Point& p1, const Point& p2, double r);

	Ellipse(const Ellipse& other);

	Ellipse& operator=(const Ellipse& other);

	std::pair<Point, Point> focuses() const;

	std::pair<Line, Line> directrices() const;

	double eccentricity() const;

	Point center() const;

	virtual bool operator==(const Shape& other) override;

	virtual bool isCongruentTo(const Shape& other) override;

	virtual bool isSimilarTo(const Shape& other) override;

	virtual double perimeter() override;

	virtual double area() override;

	virtual bool containsPoint(const Point & p) override;

	virtual void rotate(const Point& center, double angle) override;

	virtual void reflex(const Point& center) override;

	virtual void reflex(const Line& axis) override;

	virtual void scale(const Point& center, double coef) override;

	friend std::ostream& operator<<(std::ostream& out, const Ellipse& e);

protected:

	Point c, f1, f2;
	double a, b;
};