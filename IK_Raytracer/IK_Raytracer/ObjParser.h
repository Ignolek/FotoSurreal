#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "vec3.h"

class ObjParser
{
public:
	ObjParser();
	static void ParseFile(const std::string& path, std::vector<vec3>& vertices, std::vector<vec3>& faces, std::vector<vec3>& normals, std::vector<vec3>& normalsFaces);

};

