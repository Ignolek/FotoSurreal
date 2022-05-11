#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	vec3 color;
	vec3 direction = vec3(0.0f, 0.0f, 0.0f);

	DirectionalLight(vec3 col, vec3 dir) : color(col), direction(dir){}
	vec3 getDiffuse(hitRecord& rec);
	vec3 getSpecular(hitRecord& rec, vec3 cameraPos);

	bool isInShadow(hitRecord& rec);

	float getRed();
	float getGreen();
	float getBlue();
};

