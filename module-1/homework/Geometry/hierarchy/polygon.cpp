#include "polygon.h"

Polygon::Polygon(const std::vector<Point>& v): 
	vert(v) 
{}

Polygon::Polygon(const Polygon& other): 
	vert(other.vert) 
{}

Polygon& Polygon::operator=(const Polygon& other) {
	if (this == &other)
		return *this;

	vert = other.vert;
	return *this;
}

std::size_t Polygon::verticesCount() const {
	return this->vert.size();
}

std::vector<Point> Polygon::getVertices() const {
	return this->vert;
}

std::vector<double> Polygon::getAngles() const {
	std::vector<double> angles;
	Point vec1 = vert.back() - vert[0];
	Point vec2 = vert[1] - vert[0];
	angles.push_back(atan2(vec1 ^ vec2, vec1 * vec2));

	for (std::size_t i = 1; i < verticesCount() - 1; i++) {
		vec1 = vert[i - 1] - vert[i];
		vec2 = vert[i + 1] - vert[i];
		
		angles.push_back(atan2(vec1 ^ vec2, vec1 * vec2));
	}

	vec1 = vert[verticesCount() - 2] - vert.back();
	vec2 = vert[0] - vert.back();
	angles.push_back(atan2(vec1 ^ vec2, vec1 * vec2));

	return angles;
}

bool Polygon::isConvex() const {
	Point vec1 = vert[1] - vert[0];
	Point vec2 = vert[0] - vert.back();
	bool zn = (vec1 ^ vec2) > eps;

	for (std::size_t i = 1; i < verticesCount(); i++) {
		vec1 = vert[(i + 1) % verticesCount()] - vert[i];
		vec2 = vert[i] - vert[i - 1];
		
		double cross_prod = vec1 ^ vec2;
		if ((cross_prod > eps) != zn && fabs(cross_prod) > eps)
			return false;
	}

	return true;
}

bool Polygon::operator==(const Shape& other) {
	const Polygon* ptr = dynamic_cast<const Polygon*>(&other);
	if (ptr == nullptr)
		return false;

	if (ptr->verticesCount() != verticesCount())
		return false;
		
	std::size_t pos = ptr->verticesCount() + 1;
	for (std::size_t i = 0; i < ptr->verticesCount(); i++)
		if (ptr->vert[i] == vert[0]) {
			pos = i;
			break;
		}

	if (pos == ptr->verticesCount() + 1)
		return false;

	bool is_equal = true;
	for (std::size_t i = 0; i < verticesCount(); i++) {
		is_equal &= (ptr->vert[pos] == vert[i]);
		pos = (pos + 1) % ptr->verticesCount();
	}

	return is_equal;
}

bool Polygon::isCongruentTo(const Shape& other) {
	const Polygon* ptr = dynamic_cast<const Polygon*>(&other);
	if (ptr == nullptr)
		return false;

	if (this->isSimilarTo(*ptr) == false)
		return false;


	std::size_t pos = get_corresponding_vertice(*this, *ptr);
	for (std::size_t i = 0; i < ptr->verticesCount(); i++) {
		double k = get_similarity_coefficient(*this, *ptr, pos, i);
		if (fabs(k - 1) > eps)
			return false;

		pos = (pos + 1) % verticesCount();
	} 

	return true;
}

bool Polygon::isSimilarTo(const Shape& other) {
	const Polygon* ptr = dynamic_cast<const Polygon*>(&other);
	if (ptr == nullptr)
		return false;

	if (ptr->verticesCount() != verticesCount())
		return false;

	std::size_t pos = get_corresponding_vertice(*this, *ptr);
	if (pos == verticesCount() + 1)
		return false;

	double k = get_similarity_coefficient(*this, *ptr, pos, 0);
	for (std::size_t i = 1; i < ptr->verticesCount(); i++) {
		pos = (pos + 1) % verticesCount();
		double curr_k = get_similarity_coefficient(*this, *ptr, pos, i);

		if (fabs(curr_k - k) > eps)
			return false;
	} 

	return true;
}

double Polygon::perimeter() {
	if (vert.size() <= 1)
		return 0;

	double result = 0;
	for (std::size_t i = 0; i + 1 < vert.size(); i++)
		result += dist(vert[i], vert[i + 1]);

	return result += dist(vert[0], vert.back());
}

double Polygon::area() {
	if (vert.size() <= 2)
		return 0;

	double result = 0;
	for (std::size_t i = 0; i + 1 < vert.size(); i++)
		result += (vert[i] ^ vert[i + 1]);
	result += (vert.back() ^ vert[0]);

	return fabs(result / 2);
}

bool Polygon::containsPoint(const Point& p) {
	double ang = 0;
	for (std::size_t i = 0; i + 1 < vert.size(); i++) {
		if (p.onSegment(vert[i], vert[i + 1]))
			return true;

		Point vec1 = vert[i] - p;
		Point vec2 = vert[i + 1] - p;
		ang += atan2(vec1 ^ vec2, vec1 * vec2);	
	}
	
	if (p.onSegment(vert[0], vert.back()))
		return true;

	Point vec1 = vert.back() - p;
	Point vec2 = vert[0] - p;
	ang += atan2(vec1 ^ vec2, vec1 * vec2);
	return (fabs(ang) > 0);
}

void Polygon::rotate(const Point& center, double ang) {
	ang = pi * ang / 180;

	for (std::size_t i = 0; i < vert.size(); i++) {
		Point vec = vert[i] - center;
		vert[i] = vec.rotate(ang) + center;
	}
}

void Polygon::reflex(const Point& center) {
	for (std::size_t i = 0; i < vert.size(); i++)
		vert[i] = 2 * (center - vert[i]) + vert[i]; 
}

void Polygon::reflex(const Line& axis) {
	for (std::size_t i = 0; i < vert.size(); i++) {
		double len = axis.dist(vert[i]);

		Point norm(axis.a, axis.b);

		norm = (len / norm.len()) * norm;
		if (axis.dist(vert[i] + norm) > eps)
			norm = -1 * norm;

		vert[i] = 2 * norm + vert[i];
	}
}

void Polygon::scale(const Point& center, double coef) {
	for (std::size_t i = 0; i < vert.size(); i++)
		vert[i] = coef * (vert[i] - center);
}

std::ostream& operator<<(std::ostream& out, const Polygon& p) {
	for (std::size_t i = 0; i < p.vert.size(); i++)
		out << p.vert[i] << " ";
	return out;
}

std::size_t Polygon::get_corresponding_vertice(const Polygon& a, 
											   const Polygon& b) {
	std::vector <double> angles1 = a.getAngles();
	std::vector <double> angles2 = b.getAngles();

	bool is_similar = false;
	std::size_t pos = a.verticesCount() + 1;
	for (std::size_t i = 0; i < a.verticesCount(); i++) {
 		if (angles1[i] != angles2[0])
			continue;

		is_similar = true;
		for (std::size_t j = 0; j < b.verticesCount(); j++)
			if (angles1[(i + j) % a.verticesCount()] != angles2[j]) {
				is_similar = false;
				break;
			}

		if (is_similar) {
			pos = i;
			break;
		}
	}	

	return pos;
}

double Polygon::get_similarity_coefficient(const Polygon& a, 
										   const Polygon& b, 
										   std::size_t pos1, 
										   std::size_t pos2) {
	double len1 = (a.vert[(pos1 + 1) % a.verticesCount()] - a.vert[pos1]).len();
	double len2 = (b.vert[(pos2 + 1) % b.verticesCount()] - b.vert[pos2]).len();
	return len1 / len2;
}