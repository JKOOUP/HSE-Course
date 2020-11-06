#pragma once
#include "rectangle.h"
#include "circle.h"

class Square : public Rectangle {

public:

	Square() = default;

	Square(const Point& a, const Point& b);

	Square(const Square& other);

	Square& operator=(const Square& other);

	Circle circumscribedCircle() const;

	Circle inscribedCircle() const;
};