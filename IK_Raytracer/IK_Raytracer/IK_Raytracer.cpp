#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Sphere.h"
#include "XYRect.h"
#include "YZRect.h"
#include "XZRect.h"
#include "Plane.h"
#include "Triangle.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "LightIntensity.h"
#include "HitableList.h"
#include "ObjParser.h"
#include "Mesh.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "ImageTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries/stb_image.h"

int main()
{
    // Screen resolution
    int scrWidth = 200* 16;
    int scrHeight = 200 * 9;

    // Image
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    // Camera and rays settings
    float fov = 90.0f;
    vec3 lookAtPoint(0, 0, 0);
    //Camera* cam = new Camera(vec3(3, 10, -5), lookAtPoint, vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));
    Camera* cam = new Camera(vec3(0, 2, -10), lookAtPoint, vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));

    float pixelWidth = 2.0f / float(scrWidth);
    float pixelHeight = 2.0f / float(scrHeight);

    // Antyaliasing switch
    bool isAntyalia = true;

    std::cout << "Do you want to turn on antyaliasing [0 -- no, 1 -- yes]?: ";
    std::cin >> isAntyalia;

    // Load textures
    int nX, nY, nN;
    unsigned char* earthTexData = stbi_load("brick.jpg", &nX, &nY, &nN, 0);


    // Material prefabs
    std::vector<Material*> materials;

    Material* earthMat = new Material(new ImageTexture(earthTexData, nX, nY), vec3(255, 255, 255), 32);

    Material* grassMat = new Material(vec3(0, 20, 0), vec3(100, 255, 20), vec3(0, 0, 0), 64);
    materials.push_back(grassMat);

    Material* redMat = new Material(vec3(20, 0, 0), vec3(500, 0, 0), vec3(50, 50, 50), 64);
    materials.push_back(redMat);

    Material* blueMat = new Material(vec3(0, 0, 20), vec3(0, 0, 500), vec3(50, 50, 50), 64);
    materials.push_back(redMat);

    Material* whiteMat = new Material(vec3(10, 10, 10), vec3(255, 255, 255), vec3(50, 50, 50), 64);
    materials.push_back(whiteMat);

    Material* transMat = new Material(vec3(255, 255, 255), vec3(255, 255, 255), vec3(255, 255, 255), 1, true);
    //materials.push_back(transMat);

    Material* refractMat = new Material(vec3(255, 255, 255), vec3(255, 255, 255), 8, true, 1.5);
    //materials.push_back(refractMat);

    Material* mirrorMat = new Material(vec3(255, 255, 255), vec3(255, 255, 255), 8, 1.0, true);
    //materials.push_back(mirrorMat);

    // Vector of hitable objects
    std::vector<Hitable*> hitables;

    // Parser object which is used to assign vertices and indices of object to those vertices and indices given below
    ObjParser parser;
    std::vector<vec3> vertices, indices;

    //// Assigning vertices and indices;
    //parser.ParseFile("coneBlend2.obj", vertices, indices);

    //// Mesh made from parsed obj file

    //// Second object creation:
    //parser.ParseFile("cone.obj", vertices, indices);
    //
    //Mesh* cone = new Mesh(vertices, indices, 3, vec3(-3, 1, 0), new Material(vec3(60, 6, 6), vec3(200, 20, 20), vec3(255, 255, 255)));
    //cone->addToWorld(&hitables);
    //vertices.clear();
    //indices.clear();

    // ---------------- SPHERES -----------------

    Hitable* sphereMirror = new Sphere(vec3(2, 0, 1), 2, mirrorMat);
    hitables.push_back(sphereMirror);
    
    Hitable* sphereRefract = new Sphere(vec3(-2, 0, -1), -2, refractMat);
    hitables.push_back(sphereRefract);

    Hitable* sphereTextured = new Sphere(vec3(-6, -1, 5), 1, earthMat);
    hitables.push_back(sphereTextured);

    // ---------------- CORNEL -----------------
    Hitable* backRect = new XYRect(-6, 6, -3, 10, 5, whiteMat, true);
    hitables.push_back(backRect);

    Hitable* frontRect = new XYRect(-6, 6, -3, 10, -10, whiteMat, false);
    hitables.push_back(frontRect);

    Hitable* rightRect = new YZRect(-3, 10, -10, 5, 6, blueMat, true);
    hitables.push_back(rightRect);

    Hitable* leftRect = new YZRect(-3, 10, -10, 5, -6, redMat, false);
    hitables.push_back(leftRect);

    Hitable* bottomRect = new XZRect(-10, 10, -10, 5, -2, grassMat, true);
    hitables.push_back(bottomRect);

    Hitable* topRect = new XZRect(-10, 10, -10, 5, 10, whiteMat, false);
    hitables.push_back(topRect);

    // ---------------- LIGHTS -----------------
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;

    pointLights.push_back(PointLight(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0, 9.5, -1), 0.5f, 200.0f, 8.0f, 700.0f));

    std::cout << hitables.size() << std::endl;

    vec3 surLiPos = vec3(0, 1, 5);
    int surLiSize = 2;
    float surLiIntensity = 200 / (surLiSize * surLiSize);
    float lightSourceStep = .5f;

    /*for (int i = 0; i < surLiSize; i++)
    {
        for (int j = 0; j < surLiSize; j++)
    		pointLights.push_back(PointLight(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(surLiPos.x() + i * lightSourceStep, surLiPos.y() + j * lightSourceStep, surLiPos.z()), 0.5f, 20.0f, 2.0f, surLiIntensity));
    }*/
     
    // PointLights gizmos
    for (int i = 0; i < pointLights.size(); i++)
    {
        hitables.push_back(new Sphere(pointLights.at(i).location, 0.2, new Material(pointLights.at(i).diffuseColor * 1020, vec3(255, 255, 255), 1, true)));
    }
    
    // pass hitables to world
    Hitable* world = new HitableList(hitables);
    for (int i = 0; i < scrWidth; i++)
    {
        for (int j = 0; j < scrHeight; j++)
        {
            Ray r;
            LightIntensity finalColor;

            float u = float(i) / float(scrWidth);
            float v = float(j) / float(scrHeight);

            float uMin = u - (pixelWidth / 2);
            float uMax = u + (pixelWidth / 2);

            float vMin = v - (pixelHeight / 2);
            float vMax = v + (pixelHeight / 2);

            if (isAntyalia)
                finalColor = finalColor.Antialiasing(world, cam, fov, fov / 45.0f, false,
                                                     uMin, uMax, vMin, vMax, i, j, 0.50f,
                                                     std::vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr}, pointLights, directionalLights);
            if (isAntyalia == false)
            {
                r = cam->getRay(u, v, fov, fov / 45, false);
                LightIntensity newColor = finalColor.GetColorFromRay(r, world, cam->origin, pointLights, directionalLights, 0);

                perspective->SetPixel(i, j, newColor);
            }

            else
                perspective->SetPixel(i, j, finalColor);
        }

        std::cout << "Please wait, " << (i * 100) / scrWidth << "% of image has been calculated." << std::endl;
    }
    

    perspective->Write("perspective.png");
    std::cout << "Pespective image created!" << std::endl;

    return 0;
}
