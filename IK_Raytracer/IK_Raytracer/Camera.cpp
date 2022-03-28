#include "Camera.h"
#include "Sphere.h"

Camera::Camera() : position(0, 0, 0), target(0, 0, 1), up(0, 1, 0), nearPlane(1), farPlane(1000){}

Camera::Camera(Vector _position, Vector _target, float _nearPlane, float _farPlane)
{
	this->position = _position;
	this->target = _target;
	this->up = Vector(0, 1, 0);

	this->nearPlane = _nearPlane;
	this->farPlane = _farPlane;
}

Camera::~Camera(){}
