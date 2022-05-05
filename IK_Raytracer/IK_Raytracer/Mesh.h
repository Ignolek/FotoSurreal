#pragma once
#include <vector>
#include "Triangle.h"
class Mesh
{
public:
	std::vector<vec3> vertices;
	std::vector<vec3> indices;
	std::vector<Hitable*> mesh;

	vec3 position = vec3(0.0, 0.0, 0.0);
	float scale;

	Mesh(std::vector<vec3> meshVert, std::vector<vec3> meshIndi, float scl, vec3 pos);
	~Mesh();

	void setScale(float scl);
	void addToWorld(std::vector<Hitable*> *world);
};

