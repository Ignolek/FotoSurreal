#pragma once
#include "Vector.h"
#include "Ray.h"
class Camera
{
public:
	Vector position, target, up;
	float nearPlane, farPlane;

	Camera();
	Camera(Vector _position, Vector _target, float _nearPlane, float _farPlane);
	~Camera();

	Ray render(float scrWidth, float scrHeight, int currentX, int currentY, float pixelSie);
};

