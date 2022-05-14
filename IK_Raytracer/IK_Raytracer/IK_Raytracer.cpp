#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Sphere.h"
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
#include <thread>

int main()
{
    // Screen resolution
    int scrWidth = 1000;
    int scrHeight = 500;

    // Image
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    // Camera and rays settings
    float fov = 90.0f;
    vec3 lookAtPoint(0, -1, 0);
    Camera* cam = new Camera(vec3(3, 10, -5), lookAtPoint, vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));

    float pixelWidth = 2.0f / float(scrWidth);
    float pixelHeight = 2.0f / float(scrHeight);

    // Antyaliasing switch
    bool isAntyalia = true;

    std::cout << "Do you want to turn on antyaliasing [0 -- no, 1 -- yes]?: ";
    std::cin >> isAntyalia;

    // Material prefabs
    std::vector<Material*> materials;

    Material* blackMat = new Material(vec3(6, 6, 6), vec3(20, 20, 20), vec3(255, 255, 255), 32);
    materials.push_back(blackMat);

    Material* grassMat = new Material(vec3(0, 20, 0), vec3(100, 255, 20), vec3(40, 100, 0), 8);
    materials.push_back(grassMat);

    Material* goldMat = new Material(vec3(20, 20, 0), vec3(255, 255, 0), vec3(255, 255, 255), 64);
    materials.push_back(goldMat);

    Material* redMat = new Material(vec3(20, 0, 0), vec3(255, 0, 0), vec3(255, 255, 255), 32);
    materials.push_back(redMat);

    Material* silverMat = new Material(vec3(10, 10, 10), vec3(100, 100, 100), vec3(255, 255, 255), 32);
    materials.push_back(silverMat);

    Material* whiteMat = new Material(vec3(30, 10, 10), vec3(255, 255, 255), vec3(50, 50, 50), 16);
    materials.push_back(whiteMat);

    Material* transMat = new Material(vec3(255, 255, 255), vec3(255, 255, 255), vec3(255, 255, 255), 1, true);
    //materials.push_back(transMat);

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

    // green sphere which simulates ground
    Hitable* ground = new Sphere(vec3(0, -101, -1), 100.0, grassMat);
    hitables.push_back(ground);

    
    Hitable* sphere = new Sphere(vec3(4, 0, -1), 2, goldMat);
    hitables.push_back(sphere);
    
    /*Hitable* sphere1 = new Sphere(vec3(0, 0, -1), 2, vec3(0, 154, 23), new Material(vec3(0, 0, 0), vec3(30, 30, 30), vec3(255, 255, 255), 128));
    hitables.push_back(sphere1);*/
    
    Hitable* sphere2 = new Sphere(vec3(-4, 0, -1), 2, redMat);
    hitables.push_back(sphere2);

    Hitable* sphere3 = new Sphere(vec3(-6, 0, 5), 2, whiteMat);
    hitables.push_back(sphere3);

    Hitable* sphere4 = new Sphere(vec3(6, 0, 5), 2, silverMat);
    hitables.push_back(sphere4);


    int size = 3;
    float maxF = 20;
    float minF = -20;
    // random spheres generator
    for (int i = -size; i < size; i++)
    {
        for (int j = -size; j < size; j++)
        {
            float step = ((float(rand()) / float(RAND_MAX)) *            (maxF - minF)) + minF;
            float step2 = ((float(rand()) / float(RAND_MAX)) *           (maxF - minF)) + minF;
            float step3 = ((float(rand()) / float(RAND_MAX)) *           (maxF - minF)) + minF;
            float randomPosition = ((float(rand()) / float(RAND_MAX)) *  (maxF - minF)) + minF;
            float randomPosition2 = ((float(rand()) / float(RAND_MAX)) * (maxF - minF)) + minF;
            float randomPosition3 = ((float(rand()) / float(RAND_MAX)) * (maxF - minF)) + minF;

            float randomRadius = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1)));
            int randomMat = rand() % materials.size();
            hitables.push_back(new Sphere(vec3((step + randomPosition),
                                               (step2 + randomPosition2),
                                               (step3 + randomPosition3)),
                                                randomRadius, materials.at(randomMat)));
        }
    }

    std::cout << hitables.size() << std::endl;

    //Hitable* plane = new Plane(vec3(0, 5, 0), vec3(5, 0, 0), vec3(0, 5, 0), new Material(vec3(0, 0, 0), vec3(0.1, 154, 23), vec3(255, 255, 255), 256));
    //Hitable* plane = new Plane(1, -4, 4, -1, new Material(vec3(0, 0, 0), vec3(0.1, 154, 23), vec3(255, 255, 255), 256));
    //hitables.push_back(plane);


    // Lights
    std::vector<PointLight> pointLights;
    std::vector<DirectionalLight> directionalLights;

    //pointLights.push_back(PointLight(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0, 5, 5), 0.5f, 20.0f, 2.0f, 100.0f));
    //pointLights.push_back(PointLight(vec3(0.3, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0, 5, -5), 0.5f, 20.0f, 2.0f, 100.0f));
    //pointLights.push_back(PointLight(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0, 1, 5), 0.5f, 20.0f, 2.0f, 100.0f, &hitables));
    directionalLights.push_back(DirectionalLight(vec3(1, 0.8, 0.8), vec3(1, 0.8, 0.8), vec3(-3, -1, -1), 1.0f));

    for (int i = 0; i < pointLights.size(); i++)
    {
        hitables.push_back(new Sphere(pointLights.at(i).location, 0.2, new Material(pointLights.at(i).diffuseColor * 255, vec3(255, 255, 255), 1, true)));
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
