#include "Mesh.h"

Mesh::Mesh(std::vector<vec3> meshVert, std::vector<vec3> meshIndi, std::vector<vec3> meshNormals, std::vector<vec3> meshNormalsFaces, float scl, vec3 pos, Material* mMaterial)
{
	vertices = meshVert;
	indices = meshIndi;
	normals = meshNormals;
	normalsFaces = meshNormalsFaces;
	position = pos;
	meshMaterial = mMaterial;

	scale = scl;

	for (int i = 0; i < indices.size(); i++)
	{
		Hitable* meshTriangle = new Triangle(vertices.at(indices.at(i).x()) * scale + position,
											 vertices.at(indices.at(i).y()) * scale + position,
											 vertices.at(indices.at(i).z()) * scale + position,

											 normals.at(normalsFaces.at(i).y()) * scale + position,
											 vec3(200, 50, 50), meshMaterial);
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