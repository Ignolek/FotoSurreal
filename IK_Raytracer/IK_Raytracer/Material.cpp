#include "Material.h"

Material::Material() : mAmbient(vec3(100, 100, 100)), mDiffuse(vec3(100, 100, 100)), mSpecular(vec3(100, 100, 100)), shininess(32) {}
Material::Material(vec3 diffuse, vec3 specular, float shine) : mAmbient(diffuse * 0.2), mDiffuse(diffuse), mSpecular(specular), shininess(shine){}
Material::Material(vec3 diffuse, vec3 specular, float shine, bool isTrans) : mAmbient(diffuse * 0.2), mDiffuse(diffuse), mSpecular(specular), shininess(shine), isTransparent(isTrans){}
Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine) : mAmbient(ambient), mDiffuse(diffuse), mSpecular(specular), shininess(shine) {}
Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, float shine, bool isTrans) : mAmbient(ambient), mDiffuse(diffuse), mSpecular(specular), shininess(shine), isTransparent(isTrans) {}