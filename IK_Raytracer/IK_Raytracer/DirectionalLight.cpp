#include "DirectionalLight.h"

vec3 DirectionalLight::getDiffuse(hitRecord& rec)
{
	diffColor *= dot(normalize(rec.normal), normalize(unit_vector(-direction)));
	return vec3(getRed(diffColor.r()), getGreen(diffColor.g()), getBlue(diffColor.b())) * intensity;
}

vec3 DirectionalLight::getSpecular(hitRecord& rec, vec3 cameraPos, float shininess)
{
	vec3 viewDir = normalize(cameraPos + rec.p); //raczej git
	vec3 reflectDir = unit_vector(-direction) - 2 * dot(unit_vector(-direction), rec.normal) * rec.normal;
	float specular = pow(std::max(dot(viewDir, reflectDir), 0.0f), shininess);
	specColor *= specular;
	return vec3(getRed(specColor.r()), getGreen(specColor.g()), getBlue(specColor.b())) * intensity;
}

bool DirectionalLight::isInShadow(hitRecord& rec)
{
	if (rec.t < 400) return true;
	else return false;
}