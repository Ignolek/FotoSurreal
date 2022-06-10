#pragma once
#include "vec3.h"
#include "Ray.h"
#include "ImageTexture.h"
class Material
{
public:
	vec3 mAmbient;
	vec3 mDiffuse;
	vec3 mSpecular;
	float shininess;
	float fuzz = 1.0f;
	float refraction = 1.01f;
	bool isTransparent = false;
	bool isMirror = false;
	bool isRefractor = false;
	ImageTexture* texture = nullptr;

	Material();
	Material(vec3 diffuse, vec3 specular, float shine);
	Material(ImageTexture* tex, vec3 specular, float shine);

	Material(vec3 diffuse, vec3 specular, float shine, float fuzziness);

	Material(vec3 diffuse, vec3 specular, float shine, float fuzziness, bool isMirr);
	Material(vec3 diffuse, vec3 specular, float shine, bool isRefract, float refraction);

	Material(vec3 diffuse, vec3 specular, float shine, bool isTrans);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine, bool isTrans);
};

