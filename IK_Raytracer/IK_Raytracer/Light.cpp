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

float Light::getRed()
{
	if (lightColor.r() >= 1.0f) {return 1.0f;}
	else if (lightColor.r() <= 0.0f) {return 0.0f;}
	else {return lightColor.r();}
}

float Light::getGreen()
{
	if (lightColor.g() >= 1.0f) {return 1.0f;}
	else if (lightColor.g() <= 0.0f) {return 0.0f;}
	else {return lightColor.g();}
}

float Light::getBlue()
{
	if (lightColor.b() >= 1.0f) {return 1.0f;}
	else if (lightColor.b() <= 0.0f) {return 0.0f;}
	else {return lightColor.b();}
}