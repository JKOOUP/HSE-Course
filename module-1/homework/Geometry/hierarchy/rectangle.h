#pragma once 
#include "polygon.h"

class Rectangle : public Polygon {

public:

	Rectangle() = default;

	Rectangle(const Point& a, const Point& b, double k);

	Rectangle(const Rectangle& other);

	Rectangle& operator=(const Rectangle& other);

	Point center() const;

	std::pair <Line, Line> diagonals() const;
};