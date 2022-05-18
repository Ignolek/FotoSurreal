#pragma once
#include "vec3.h"
#include "Ray.h"
class Material
{
public:
	vec3 mAmbient;
	vec3 mDiffuse;
	vec3 mSpecular;
	float shininess;
	float fuzz = 1.0f;
	bool isTransparent = false;
	bool isMirror = false;

	Material();
	Material(vec3 diffuse, vec3 specular, float shine);
	Material(vec3 diffuse, vec3 specular, float shine, float fuzziness);
	Material(vec3 diffuse, vec3 specular, float shine, float fuzziness, bool isMirr);
	Material(vec3 diffuse, vec3 specular, float shine, bool isTrans);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine, bool isTrans);
};

