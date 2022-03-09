#include "Vector.h"
#include "iostream"
#include <string>
#include <math.h>

Vector::Vector() : x( 1 ), y( 1 ), z( 1 ) {}
Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector::Vector(Vector p1, Vector p2)
{
	this->x = p2.x - p1.x;
	this->y = p2.y - p1.y;
	this->z = p2.z - p1.z;
}
Vector::~Vector(){}

std::string Vector::toString()
{
	return "Vector(" + std::to_string(x) + ", " 
					 + std::to_string(y) + ", " 
					 + std::to_string(z) + ")";
}

void Vector::normalize()
{
	float n = this->length();
	if (n != 0)
	{
		this->div(n);
	}
	else
		std::cout << "Can't divide by 0 [Normalize]" << std::endl;
}

Vector Vector::normalizeProduct()
{
	Vector* newV = new Vector(this->x, this->y, this->z);
	float n = this->length();
	if (n != 0)
	{
		newV->div(n);
		return *newV;
	}
	else
		return *newV;
}

float Vector::length()
{
	return (float)sqrt(pow(this->x, 2) + 
					   pow(this->y, 2) + 
					   pow(this->z, 2));
}

float Vector::lengthSquared()
{
	return (float)(pow(this->x, 2) + 
				   pow(this->y, 2) + 
				   pow(this->z, 2));
}

float Vector::dot(Vector v)
{
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vector Vector::cross(Vector v)
{
	return Vector(this->y * v.z - this->z * v.y, 
				  this->z * v.x - this->x * v.z, 
				  this->x * v.y - this->y * v.x);
}

void Vector::negate()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

void Vector::add(Vector v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Vector::sub(Vector v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Vector::div(float f)
{
	if (f != 0)
	{
		this->x /= f;
		this->y /= f;
		this->z /= f;
	}
	else
		std::cout << "Can't divide by 0 [Div]" << std::endl;
}

void Vector::mag(float f)
{
	this->x *= f;
	this->y *= f;
	this->z *= f;
}

#pragma region Operators
//Vector Vector::operator*(float scalar, Vector right)
//{
//	return Vector(right.x * scalar, right.y * scalar, right.z * scalar);
//}
//Vector Vector::operator*(Vector left, float scalar)
//{
//	return Vector(left.x * scalar, left.y * scalar, left.z * scalar);
//}
//Vector Vector::operator*(Vector left, Vector right)
//{
//	return Vector(left.x * right.x, left.y * right.y, left.z * right.z);
//}
//Vector Vector::operator+(Vector left, Vector right)
//{
//	return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
//}
//Vector Vector::operator-(Vector left, Vector right)
//{
//	return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
//}
//Vector Vector::operator-(Vector left)
//{
//	return Vector(-left.x, -left.y, -left.z);
//}
//bool Vector::operator==(Vector left, Vector right)
//{
//	return (left.x == right.x && left.y == right.y && left.z == right.z);
//}
//bool Vector::operator!=(Vector left, Vector right)
//{
//	return (left.x != right.x || left.y != right.y || left.z != right.z);
//}
//Vector Vector::operator/(Vector left, float scalar)
//{
//	Vector *vector = new Vector();
//	// get the inverse of the scalar up front to avoid doing multiple divides later
//	
//	float inverse = 1.0f / scalar;
//	vector->x = left.x * inverse;
//	vector->y = left.y * inverse;
//	vector->z = left.z * inverse;
//	return *vector;
//}
#pragma endregion

Vector Vector::reflect(Vector normal)
{
	return normal;
	//return this - (2 * this->dot(normal) * normal.x);
}
Vector Vector::magProduct(Vector v, float f)
{
	return Vector(v.x * f, v.y * f, v.z * f);
}
Vector Vector::toPoint()
{
	Vector *p = new Vector(this->x, this->y, this->z);
	return *p;
}
Vector Vector::lerp(Vector v, float t)
{
	Vector *vector = new Vector();
	vector->x = this->x + t * (v.x - this->x);
	vector->y = this->y + t * (v.y - this->y);
	vector->z = this->z + t * (v.z - this->z);
	return *vector;
}
