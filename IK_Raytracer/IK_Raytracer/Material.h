#pragma once
#include "vec3.h"
class Material
{
public:
	vec3 mAmbient;
	vec3 mDiffuse;
	vec3 mSpecular;
	float shininess;

	Material();
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine);
};

