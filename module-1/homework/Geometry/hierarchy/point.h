#pragma once 
#include "constants.h"

class Point {

friend class Circle;
friend class Ellipse;
friend class Line;
friend class Polygon;
friend class Rectangle;
friend class Shape;
friend class Square;
friend class Triangle;

public:

	Point() = default;

	Point(double _x, double _y);

	Point(const Point& p);

	Point& operator=(const Point& p);		

	double len() const;

	Point rotate(double ang);

	bool onSegment(const Point& a, const Point& b) const;

	friend bool operator==(const Point& a, const Point& b);

	friend bool operator!=(const Point& a, const Point& b);

	friend double dist(const Point& a, const Point& b);

	friend Point operator*(double coef, const Point& p);

	friend Point operator*(const Point& p, double coef);

	friend double operator*(const Point& a, const Point& b); /// scalar product

	friend double operator^(const Point& a, const Point& b); /// cross product

	friend Point operator-(const Point& a, const Point& b);

	friend Point operator+(const Point& a, const Point& b);

	friend std::ostream& operator<<(std::ostream& out, const Point& p);

private:

	double x;
	double y;
};