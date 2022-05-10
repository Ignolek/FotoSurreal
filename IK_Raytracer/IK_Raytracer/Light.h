#pragma once
#include "vec3.h"
#include "Hitable.h"

class Light
{
public:
	vec3 lightColor;

	Light();
	Light(vec3 color);

	void add(vec3 colorToAdd);
	void sub(vec3 colorToSub);

	float getRed();
	float getGreen();
	float getBlue();
};

