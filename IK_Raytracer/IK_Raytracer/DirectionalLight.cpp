#include "DirectionalLight.h"

vec3 DirectionalLight::getDiffuse(hitRecord& rec)
{
	// Diffuse jest okay
	diffColor *= dot(normalize(rec.normal), normalize(unit_vector(-direction)));
	return vec3(getRed(diffColor.r()), getGreen(diffColor.g()), getBlue(diffColor.b()));
}

vec3 DirectionalLight::getSpecular(hitRecord& rec, vec3 cameraPos, float shininess)
{
	// Specular ma odbicia po zlej stronie
	vec3 viewDir = normalize(cameraPos + rec.p); //raczej git
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