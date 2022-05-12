#include "DirectionalLight.h"

vec3 DirectionalLight::getDiffuse(hitRecord& rec)
{
	diffColor *= dot(normalize(rec.normal), normalize(unit_vector(-direction)));
	return vec3(getRed(diffColor.r()), getGreen(diffColor.g()), getBlue(diffColor.b()));
}

vec3 DirectionalLight::getSpecular(hitRecord& rec, vec3 cameraPos, float shininess)
{
	vec3 viewDir = normalize(cameraPos - rec.p); //raczej git
	vec3 reflectDir = unit_vector(-direction) - 2 * dot(unit_vector(-direction), rec.normal) * rec.normal;
	float specular = pow(std::max(dot(viewDir, reflectDir), 0.0f), shininess);
	specColor *= specular;
	return vec3(getRed(specColor.r()), getGreen(specColor.g()), getBlue(specColor.b()));
}

bool DirectionalLight::isInShadow(hitRecord& rec)
{
	Ray* rayToLightSource = new Ray(rec.p, -direction);
	
	return false;
}

float DirectionalLight::getRed(float red)
{
	if (red >= 1.0f) { return 1.0f; }
	else if (red <= 0.0f) { return 0.0f; }
	else { return red; }
}

float DirectionalLight::getGreen(float green)
{
	if (green >= 1.0f) { return 1.0f; }
	else if (green <= 0.0f) { return 0.0f; }
	else { return green; }
}

float DirectionalLight::getBlue(float blue)
{
	if (blue >= 1.0f) { return 1.0f; }
	else if (blue <= 0.0f) { return 0.0f; }
	else { return blue; }
}