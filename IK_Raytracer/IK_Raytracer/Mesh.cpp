#include "Mesh.h"

Mesh::Mesh(std::vector<vec3> meshVert, std::vector<vec3> meshIndi, float scl, vec3 pos, Material* meshMat)
{
	vertices = meshVert;
	indices = meshIndi;
	position = pos;
	meshMaterial = meshMat;

	scale = scl;

	for (int i = 0; i < indices.size(); i++)
	{
		Hitable* meshTriangle = new Triangle(vertices.at(indices.at(i).x()) * scale - position,
							vertices.at(indices.at(i).y()) * scale - position,
							vertices.at(indices.at(i).z()) * scale - position, 
							meshMaterial);
		mesh.push_back(meshTriangle);
	}
}

void Mesh::setScale(float scl)
{
	scale = scl;
}

void Mesh::addToWorld(std::vector<Hitable*> *world)
{
	for (int i = 0; i < mesh.size(); i++)
	{
		world->push_back(mesh.at(i));
	}
}