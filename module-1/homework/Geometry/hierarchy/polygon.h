#pragma once
#include "shape.h"

class Polygon : public Shape {

public:

    Polygon() = default;

    Polygon(const std::vector<Point>& v);

    Polygon(const Polygon& other);

    Polygon& operator=(const Polygon& other);

    std::size_t verticesCount() const;

    std::vector<Point> getVertices() const;

    std::vector<double> getAngles() const;

    bool isConvex() const;

    virtual bool operator==(const Shape& other) override;

    virtual bool isCongruentTo(const Shape& other) override;

    virtual bool isSimilarTo(const Shape& other) override;  

    virtual double perimeter() override;

    virtual double area() override;

    virtual bool containsPoint(const Point& p) override;

    virtual void rotate(const Point& center, double ang) override;

    virtual void reflex(const Point& center) override;

    virtual void reflex(const Line& axis) override;

    virtual void scale(const Point& center, double coef) override;

    friend std::ostream& operator<<(std::ostream& out, const Polygon& p);

protected:

    std::vector<Point> vert; 

    static std::size_t get_corresponding_vertice(const Polygon& a, 
                                                 const Polygon& b);

    static double get_similarity_coefficient(const Polygon& a, 
                                             const Polygon& b, 
                                             std::size_t pos1, 
                                             std::size_t pos2);
};