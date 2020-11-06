#pragma once
#include "point.h"

class Line {

friend class Circle;
friend class Ellipse;
friend class Polygon;
friend class Rectangle;
friend class Shape;
friend class Square;

public: 

	Line() = default;

	Line(const Point& p1, const Point& p2);

	Line(const Line& other);

	Line& operator=(const Line& other);

	double dist(const Point& p) const;

	friend bool operator==(const Line& l1, const Line& l2);

	friend bool operator!=(const Line& l1, const Line& l2);	

private:

	double a, b, c;
};