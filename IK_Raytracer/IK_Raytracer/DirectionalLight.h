#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	vec3 ambientColor;
	vec3 diffColor;
	vec3 specColor;
	vec3 direction = vec3(0.0f, 0.0f, 0.0f);
	float intensity;

	DirectionalLight(vec3 diffCol, vec3 specCol, vec3 dir, float intense) : ambientColor(diffCol * 3), diffColor(diffCol), specColor(specCol), direction(dir), intensity(intense){}
	vec3 getDiffuse(hitRecord& rec);
	vec3 getSpecular(hitRecord& rec, vec3 cameraPos, float shininess);
};

