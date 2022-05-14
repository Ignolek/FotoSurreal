#pragma once
#include "vec3.h"
class Material
{
public:
	vec3 mAmbient;
	vec3 mDiffuse;
	vec3 mSpecular;
	float shininess;
	bool isTransparent = false;

	Material();
	Material(vec3 diffuse, vec3 specular, float shine);
	Material(vec3 diffuse, vec3 specular, float shine, bool isTrans);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine, bool isTrans);
};

