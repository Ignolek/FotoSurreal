#pragma once
#include <vector>
#include "Triangle.h"
#include "Material.h"

class Mesh
{
public:
	std::vector<vec3> vertices;
	std::vector<vec3> indices;
	std::vector<vec3> normals;
	std::vector<vec3> normalsFaces;
	std::vector<Hitable*> mesh;
	Material* meshMaterial;

	vec3 position = vec3(0.0, 0.0, 0.0);
	float scale;

	Mesh(std::vector<vec3> meshVert, std::vector<vec3> meshIndi, std::vector<vec3> meshNormals, std::vector<vec3> meshNormalsFaces, float scl, vec3 pos, Material* mMaterial);
	~Mesh();

	void setScale(float scl);
	void addToWorld(std::vector<Hitable*> *world);
};

