#pragma once
#include "vec3.h"
class Material
{
public:
	vec3 mAmbient;
	vec3 mDiffuse;
	vec3 mSpecular;

	Material();
	Material(vec3 ambient, vec3 diffuse, vec3 specular);
};

