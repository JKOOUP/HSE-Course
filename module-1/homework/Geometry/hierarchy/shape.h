#pragma once
#include "line.h"
#include "point.h"

class Shape {
public:

	virtual bool operator==(const Shape& other) = 0;

	virtual bool isCongruentTo(const Shape& other) = 0;

	virtual bool isSimilarTo(const Shape& other) = 0;

	virtual double perimeter() = 0;

	virtual double area() = 0;

	virtual bool containsPoint(const Point & p) = 0;

	virtual void rotate(const Point& center, double angle) = 0;

	virtual void reflex(const Point& center) = 0;

	virtual void reflex(const Line& axis) = 0;

	virtual void scale(const Point& center, double coef) = 0;

};