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

int main()
{
    // Screen resolution
    int scrWidth = 2000;
    int scrHeight = 1000;

    // Image
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    // Camera and rays settings
    float fov = 90.0f;
    Camera* cam = new Camera(vec3(0, 0, 10), vec3(0, 0, -1000), vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));

    float pixelWidth = 2.0f / float(scrWidth);
    float pixelHeight = 2.0f / float(scrHeight);

    // Antyaliasing switch
    bool isAntyalia = true;

    std::cout << "Do you want to turn on antyaliasing [0 -- no, 1 -- yes]?: ";
    std::cin >> isAntyalia;

    // Vector of hitable objects
    std::vector<Hitable*> hitables;

    // Parser object which is used to assign vertices and indices of object to those vertices and indices given below
    ObjParser parser;
    std::vector<vec3> vertices, indices;

    //// Assigning vertices and indices;
    //parser.ParseFile("cubeTri.obj", vertices, indices);

    ////// Mesh made from parsed obj file
    //Mesh* cube = new Mesh(vertices, indices, 2, vec3(3, 1, 0) ,new Material(vec3(200, 20, 20), vec3(200, 50, 23), vec3(0, 0, 0))); // 1. vertices of object 2. indices of object 3. scale 4. position
    //cube->addToWorld(&hitables);
    //vertices.clear();
    //indices.clear();

    ////// Second object creation:
    //parser.ParseFile("coneBlend2.obj", vertices, indices);
    //
    //Mesh* cone = new Mesh(vertices, indices, 3, vec3(-3, 1, 0), new Material(vec3(200, 20, 20), vec3(0, 250, 250), vec3(0, 0, 0)));
    //cone->addToWorld(&hitables);
    //vertices.clear();
    //indices.clear();

    
 
    // green sphere which simulates ground
    Hitable* ground = new Sphere(vec3(0, -101, -1), 100, vec3(0, 154, 23), new Material(vec3(0, 45, 6), vec3(0, 154, 23), vec3(0, 0, 0)));
    hitables.push_back(ground);
    
    Hitable* sphere = new Sphere(vec3(3, 1, -1), 2, vec3(0, 154, 23), new Material(vec3(60, 60, 15), vec3(200, 200, 50), vec3(0, 0, 0)));
    hitables.push_back(sphere);
    
    Hitable* sphere1 = new Sphere(vec3(-3, 3, -1), 2, vec3(0, 154, 23), new Material(vec3(60, 60, 60), vec3(200, 200, 200), vec3(0, 0, 0)));
    hitables.push_back(sphere1);
    std::cout << hitables.size() << std::endl;
    
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
                    std::vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr});


            float pixelCenterX = u + pixelWidth;
            float pixelCenterY = v + pixelHeight;


            if (isAntyalia == false)
            {
                r = cam->getRay(u, v, fov, fov / 45, false);
                LightIntensity newColor = finalColor.GetColorFromRay(r, world, 0);

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
