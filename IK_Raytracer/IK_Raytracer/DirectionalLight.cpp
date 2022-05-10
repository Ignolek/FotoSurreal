#include "DirectionalLight.h"

vec3 DirectionalLight::getDiffuse(hitRecord& rec)
{
	color *= dot(normalize(rec.normal), normalize(unit_vector(-direction)));
	return vec3(getRed(), getGreen(), getBlue());
}

vec3 DirectionalLight::getSpecular(hitRecord& rec)
{
	this->lightColor = rec.materialPtr->mSpecular;
	return vec3(0, 0, 0);
}

bool DirectionalLight::isInShadow(hitRecord& rec)
{
	Ray* rayToLightSource = new Ray(rec.p, -direction);
	
	return false;
}

float DirectionalLight::getRed()
{
	if (color.r() >= 1.0f) { return 1.0f; }
	else if (color.r() <= 0.0f) { return 0.0f; }
	else { return color.r(); }
}

float DirectionalLight::getGreen()
{
	if (color.g() >= 1.0f) { return 1.0f; }
	else if (color.g() <= 0.0f) { return 0.0f; }
	else { return color.g(); }
}

float DirectionalLight::getBlue()
{
	if (color.b() >= 1.0f) { return 1.0f; }
	else if (color.b() <= 0.0f) { return 0.0f; }
	else { return color.b(); }
}