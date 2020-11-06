#pragma once
#include "ellipse.h"

class Circle : public Ellipse {
public:

	Circle() = default;

	Circle(const Point& center, double r);

	Circle(const Circle& other);

	Circle& operator=(const Circle& other);

	double radius() const;

	friend std::ostream& operator<<(std::ostream& out, const Circle& c);
};