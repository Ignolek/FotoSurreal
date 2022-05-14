#pragma once
#include "Light.h"
#include "Sphere.h"
#include <vector>

class PointLight : public Light
{
public:
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float intensity;

	vec3 location;
	float attenuation;
	float linearAttenuation;
	float quatAttenuation;

	PointLight(vec3 diffColor, vec3 specColor, vec3 loc, float atten, float linearAtten, float quatAtten, float intense, std::vector<Hitable*>* hitables);
	vec3 getDiffuse(hitRecord& rec);
	vec3 getSpecular(hitRecord& rec, vec3 cameraPos, float shininess);
};

