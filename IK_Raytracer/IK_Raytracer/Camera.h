#pragma once
#include "Ray.h"
class Camera
{
public:
	vec3 lowerLeftCorner, horizontal, vertical, origin;
	Camera()
	{
		lowerLeftCorner = vec3(-2.0, -1.0f, -1.0f);
		horizontal = vec3(4.0f, 0.0f, 0.0f);
		vertical = vec3(0.0f, 2.0f, 0.0f);
		origin = vec3(0.0f, 0.0f, 0.0f);
	}
	Camera(vec3 _lowerLeftCorner, vec3 _horizontal, vec3 _vertical, vec3 _origin)
		: lowerLeftCorner(_lowerLeftCorner), horizontal(_horizontal), vertical(_vertical), origin(_origin){}
	~Camera(){}
	
	Ray getRay(float u, float v)
	{
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
};

