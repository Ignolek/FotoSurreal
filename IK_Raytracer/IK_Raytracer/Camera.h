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
	
	Camera(vec3 lookFrom, vec3 lookAt, vec3 vUp, float vFov, float aspect)
	{
		vec3 u, v, w;
		float theta = vFov * 3.1415 / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;
		w = unit_vector(lookFrom - lookAt);
		u = unit_vector(cross(vUp, w));
		v = cross(w, u);
		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
		horizontal = 2 * halfWidth * u;
		vertical = 2 * halfHeight * v;
	}
	~Camera(){}
	
	Ray getRay(float u, float v, bool ortho)
	{
		if (ortho)
			return Ray(vec3(origin.e[0] + u, origin.e[1] + v, origin.e[2]), vec3(origin.e[0] + u, origin.e[1] + v, origin.e[2] - 40000));
		else
			return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}
};

