#pragma once
#include "Light.h"

class PointLight :
    public Light
{
public:
    PointLight() {};
    float constAttenuation;
    float linearAttenuation;
    float quadAttenuation;

    vec3 getDiffuse(vec3 cameraPosition, vec3 intersectLocation) override;

};

