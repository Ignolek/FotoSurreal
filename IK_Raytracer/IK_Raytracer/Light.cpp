#include "Light.h"

Light::Light() : lightColor(0, 0, 0){}
Light::Light(vec3 color) : lightColor(color){}

void Light::add(vec3 colorToAdd)
{
	lightColor += colorToAdd;
}
void Light::sub(vec3 colorToSub)
{
	if (lightColor.r() >= 0.0f && lightColor.g() >= 0.0f && lightColor.b() >= 0.0f)
	{
		lightColor /= colorToSub;
	}
	else
	{
		lightColor = vec3(0.0f, 0.0f, 0.0f);
	}
}


float Light::getRed(float red)
{
	if (red >= 1.0f) { return 1.0f; }
	else if (red <= 0.0f) { return 0.0f; }
	else { return red; }
}

float Light::getGreen(float green)
{
	if (green >= 1.0f) { return 1.0f; }
	else if (green <= 0.0f) { return 0.0f; }
	else { return green; }
}

float Light::getBlue(float blue)
{
	if (blue >= 1.0f) { return 1.0f; }
	else if (blue <= 0.0f) { return 0.0f; }
	else { return blue; }
}