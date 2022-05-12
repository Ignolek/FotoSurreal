#include "PointLight.h"

PointLight::PointLight(vec3 diffColor, vec3 specColor, vec3 loc, float atten, float linearAtten, float quatAtten) : 
			diffuseColor(diffColor), specularColor(specColor), location(loc), attenuation(atten), linearAttenuation(linearAtten), quatAttenuation(quatAtten){}

vec3 PointLight::getDiffuse(hitRecord& rec)
{
	vec3 lightDir = normalize(location - rec.p);
	float distanceToPointLight = distance(rec.p, location);
	float finalAttenuation = attenuation + (distanceToPointLight * linearAttenuation) + (distanceToPointLight * pow(quatAttenuation, 2.0f));

	diffuseColor *= dot(normalize(rec.normal), normalize(unit_vector(lightDir)));
	diffuseColor /= finalAttenuation;
	
	return vec3(getRed(diffuseColor.r()), getGreen(diffuseColor.g()), getBlue(diffuseColor.b())) * 100;
}
vec3 PointLight::getSpecular(hitRecord& rec, vec3 cameraPos, float shininess)
{
	vec3 lightDir = normalize(location - rec.p);
	vec3 viewDir = normalize(cameraPos + rec.p); //raczej git
	vec3 reflectDir = unit_vector(lightDir) - 2 * dot(unit_vector(lightDir), -rec.normal) * -rec.normal;
	float specular = pow(std::max(dot(viewDir, reflectDir), 0.0f), shininess);
	specularColor *= specular;

	return vec3(getRed(specularColor.r()), getGreen(specularColor.g()), getBlue(specularColor.b()));
}
