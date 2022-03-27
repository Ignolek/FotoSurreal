#include "Ray.h"
Ray::Ray(const vec3& a, const vec3& b)
{
	A = a;
	B = b;
}
vec3 Ray::origin() const
{
	return A;
}
vec3 Ray::direction() const
{
	return B;
}
vec3 Ray::pointAtParameter(float t) const
{
	return A + t * B;
}
//Ray::Ray() : origin(Vector::Vector()), direction(Vector::Vector()), distance(0.0f){}
//Ray::Ray(Vector o, Vector d)
//{
//	origin = o;
//	direction = d;
//}
//Ray::~Ray(){}
//
//Vector Ray::getOrigin()
//{
//	return origin;
//}
//
//Vector Ray::getDirection()
//{
//	return direction;
//}
//
//Vector Ray::getDestination()
//{
//	return destination;
//}
