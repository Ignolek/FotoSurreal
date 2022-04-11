#pragma once
#include "Ray.h"
class Camera
{
private:
	vec3 _u, _v, _w;
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
		float theta = vFov * 3.1415 / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;
		_w = unit_vector(lookFrom - lookAt);
		_u = unit_vector(cross(vUp, _w));
		_v = cross(_w, _u);
		lowerLeftCorner = vec3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth * _u - halfHeight * _v - _w;
		horizontal = 2 * halfWidth * _u;
		vertical = 2 * halfHeight * _v;
	}
	~Camera(){}
	
	Ray getRay(float u, float v, float fov, float m, bool ortho)
	{
		fov /= 100;
		if (u < 0 || v < 0 || u > 1 || v > 1)
			return Ray(vec3(0, 0, 0), vec3(0, 0, 1));
		else
		{

			float multiplier = pow(2.42, m - 1);
			if (ortho)
				return Ray(vec3(horizontal.e[0] * u + 0.825 * multiplier, vertical.e[1] * v + fov, 0), vec3(horizontal.e[0] * u + 0.825 * multiplier, vertical.e[1] * v + fov, -1000));
			else
				return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
		}
	}
};

