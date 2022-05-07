#include "PointLight.h"

vec3 PointLight::getDiffuse(vec3 cameraPosition, vec3 intersectLocation)
{
    vec3 dist = intersectLocation - this->location;
    float fDist = dist.length();

    //float lightFactor = 1 / ((constAttenuation + linearAttenuation) * fDist);
    float lightFactor = constAttenuation + (linearAttenuation * fDist) + (quadAttenuation * (fDist*fDist));
    vec3 result = vec3(sourceColor.x(), sourceColor.y(), sourceColor.z());
    result = result / lightFactor;
    return result;
}
