#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	vec3 diffColor;
	vec3 specColor;
	vec3 direction = vec3(0.0f, 0.0f, 0.0f);

	DirectionalLight(vec3 diffCol, vec3 specCol, vec3 dir) : diffColor(diffCol), specColor(specCol), direction(dir){}
	vec3 getDiffuse(hitRecord& rec);
	vec3 getSpecular(hitRecord& rec, vec3 cameraPos, float shininess);

	bool isInShadow(hitRecord& rec);

	float getRed(float red);
	float getGreen(float green);
	float getBlue(float blue);
};

