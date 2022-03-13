#include "Ray.h"
Ray::Ray() : origin(Vector::Vector()), direction(Vector::Vector()), distance(0.0f){}
Ray::Ray(Vector o, Vector d)
{
	origin = o;
	direction = d;
}
Ray::~Ray(){}

Vector Ray::getOrigin()
{
	return origin;
}

Vector Ray::getDirection()
{
	return direction;
}

Vector Ray::getDestination()
{
	return destination;
}
