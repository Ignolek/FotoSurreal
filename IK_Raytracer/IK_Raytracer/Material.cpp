#include "Material.h"

Material::Material() : mAmbient(vec3(100, 100, 100)), mDiffuse(vec3(100, 100, 100)), mSpecular(vec3(100, 100, 100)) {}
Material::Material(vec3 ambient, vec3 diffuse, vec3 specular) : mAmbient(ambient), mDiffuse(diffuse), mSpecular(specular){}