#pragma once
#include <string>
class Vector
{
	float x, y, z;

public:
	Vector();
	Vector(float x, float y, float z);
	Vector(Vector p1, Vector p2);
	~Vector();
	Vector(const Vector &v);

	std::string toString();
	void normalize();
	Vector normalizeProduct();
	float length();
	float lengthSquared();
	Vector dot(Vector v);
	Vector cross(Vector v);
	void negate();
	void add(Vector v);
	void sub(Vector v);
	void div(float f);
	void mag(float f);

#pragma region Operators
	Vector operator*(const float&) const;
	Vector operator*(const Vector &) const;

	Vector operator+(const float&) const;
	Vector operator+(const Vector&) const;

	Vector operator-(const float&) const;
	Vector operator-(const Vector&) const;

	Vector operator/(const float&) const;
	Vector operator/(const Vector&) const;

	bool operator==(const Vector&) const;
	bool operator==(const float&) const;
	
	bool operator!=(const Vector&) const;
	bool operator!=(const float&) const;
#pragma endregion

	Vector reflect(Vector normal);
	static Vector magProduct(Vector v, float f);
	Vector toPoint();
	Vector lerp(Vector v, float t);
};

