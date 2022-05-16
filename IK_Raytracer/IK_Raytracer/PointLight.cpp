#include "PointLight.h"

PointLight::PointLight(vec3 diffColor, vec3 specColor, vec3 loc, float atten, float linearAtten, float quatAtten, float intense) :
			ambientColor(diffColor * 2.5), diffuseColor(diffColor), specularColor(specColor), location(loc), attenuation(atten), linearAttenuation(linearAtten), quatAttenuation(quatAtten), intensity(intense)
{
	//hitList->push_back(new Sphere(loc, 0.3, new Material(vec3(255, 255, 255), vec3(255, 255, 255), vec3(255, 255, 255), 1, true)));
}

vec3 PointLight::getDiffuse(hitRecord& rec)
{
	vec3 lightDir = normalize(location - rec.p);
	float distanceToPointLight = distance(rec.p, location);
	float finalAttenuation = attenuation + (distanceToPointLight * linearAttenuation) + (distanceToPointLight * pow(quatAttenuation, 2.0f));

	diffuseColor *= dot(normalize(rec.normal), normalize(unit_vector(lightDir)));
	diffuseColor /= finalAttenuation;
	
	return vec3(getRed(diffuseColor.r()), getGreen(diffuseColor.g()), getBlue(diffuseColor.b())) * intensity * (((float(rand()) / float(RAND_MAX)) * (1 - rec.materialPtr->fuzz)) + rec.materialPtr->fuzz);
}
vec3 PointLight::getSpecular(hitRecord& rec, vec3 cameraPos, float shininess)
{
	vec3 lightDir = normalize(location - rec.p);
	vec3 viewDir = normalize(cameraPos + rec.p);
	vec3 reflectDir = (unit_vector(lightDir) - 2 * dot(unit_vector(lightDir), -rec.normal) * -rec.normal);
	float specular = pow(std::max(dot(viewDir, reflectDir), 0.0f), shininess);
	specularColor *= specular;

	return vec3(getRed(specularColor.r()), getGreen(specularColor.g()), getBlue(specularColor.b())) * intensity/100 * (((float(rand()) / float(RAND_MAX)) * (1 - rec.materialPtr->fuzz)) + rec.materialPtr->fuzz);
}
