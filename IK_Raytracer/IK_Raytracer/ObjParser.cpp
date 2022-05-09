#include "ObjParser.h"

ObjParser::ObjParser()
{

}

void ObjParser::ParseFile(const std::string& path, std::vector<vec3>& vertices, std::vector<vec3>& faces, std::vector<vec3>& normals, std::vector<vec3>& normalsFaces)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "[Error]: can not open file: \"" << path << "\"" << std::endl;
        exit(-1);
    }
    std::string buffer;
    for (ifs >> buffer; !ifs.eof(); ifs >> buffer) {
        if (buffer == "v") {
            // format: v x y z
            float x, y, z;
            ifs >> x >> y >> z;
            vertices.emplace_back(x, y, z);
        }
        else if (buffer == "vn")
        {
            // format: vn x y z
            float x, y, z;
            ifs >> x >> y >> z;
            normals.emplace_back(x, y, z);
        }
        else if (buffer == "f") {
            int x, y, z, n, t;
            int nX, nY, nZ;
            std::string line;
            getline(ifs, line);
            if (line.find('/') != std::string::npos && (std::count(line.begin(), line.end(), '/') == 6 || std::count(line.begin(), line.end(), '/') == 8)) {
                // format: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
                sscanf_s(line.c_str(), " %d/%d/%d %d/%d/%d %d/%d/%d\n", &x, &t, &nX, &y, &t, &nY, &z, &t, &nZ);
            }
            else if (line.find('/') != std::string::npos && (std::count(line.begin(), line.end(), '/') == 3 || std::count(line.begin(), line.end(), '/') == 4)) {
                // format: f v1/vn1 v2/vn2 v3/vn3
                sscanf_s(line.c_str(), " %d/%d %d/%d %d/%d\n", &x, &nX, &y, &nY, &z, &nZ);
            }
            else if (line.find("//") != std::string::npos && (std::count(line.begin(), line.end(), '/') == 6 || std::count(line.begin(), line.end(), '/') == 8)) {
                // format: f v1//vn1 v2//vn2 v3//vn3
                sscanf_s(line.c_str(), " %d//%d %d//%d %d//%d\n", &x, &nX, &y, &nY, &z, &nZ);
            }
            else {
                // format: f v1 v2 v3
                sscanf_s(line.c_str(), " %d %d %d\n", &x, &y, &z);
            }
            faces.emplace_back(x - 1, y - 1, z - 1);
            normalsFaces.emplace_back(nX - 1, nY - 1, nZ - 1);
        }
    }
    ifs.close();
}
