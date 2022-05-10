#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	vec3 location;
	float attenuation;
	float linearAttenuation;
	float quatAttenuation;

	
	vec3 getDiffuse();
	vec3 getSpecular();
};

