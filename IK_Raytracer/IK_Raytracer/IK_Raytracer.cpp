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
#include "Metal.h"
#include "Lambertian.h"
#include "PointLight.h"

int main()
{
    // Screen resolution
    int scrWidth = 1000;
    int scrHeight = 500;

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


    PointLight* point = new PointLight();
    point->location = vec3(0, 0, 0);
    point->sourceColor = vec3(255, 255, 255);
    point->linearAttenuation = 0.7;
    point->constAttenuation = 3.0;
    point->quadAttenuation = 0.0001;

    // Parser object which is used to assign vertices and indices of object to those vertices and indices given below
    ObjParser parser;
    std::vector<vec3> vertices, indices, normals, normalsFaces;

    // Assigning vertices and indices;
    //parser.ParseFile("cubeBlend.obj", vertices, indices, normals, normalsFaces);
    //// Mesh made from parsed obj file
    //Mesh* cube = new Mesh(vertices, indices, normals, normalsFaces, 1.0f, vec3(-3, 1, 2), new Metal(vec3(0.8, 0.8, 0.8), 0.7)); // 1. vertices of object 2. indices of object 3. scale 4. position
    //cube->addToWorld(&hitables);
    //vertices.clear();
    //indices.clear();

    // Second object creation:
    /*parser.ParseFile("cone.obj", vertices, indices);

    Mesh* cone = new Mesh(vertices, indices, 0.5f, vec3(-3, 0, 0), new Metal(vec3(0.8, 0.8, 0.8)));
    cone->addToWorld(&hitables);
    vertices.clear();
    indices.clear();*/

    Hitable* sphere = new Sphere(vec3(5, 2, 0), 3, vec3(0, 0, 0), new Metal(vec3(0.8, 0.8, 0.8), 0.2));
    hitables.push_back(sphere);
    Hitable* sphere1 = new Sphere(vec3(0, 2, 0), 2, vec3(0, 0, 0), new Lambertian(vec3(0.2, 0.2, 0.8)));
    hitables.push_back(sphere1);    
    Hitable* sphere2 = new Sphere(vec3(-5, 2, 0), 3, vec3(0, 0, 0), new Metal(vec3(0.8, 0.5, 0.5), 0.6));
    hitables.push_back(sphere2);
 
    // green sphere which simulates ground
    Hitable* ground = new Sphere(vec3(0, -100.5, -1), 100, vec3(0, 154, 23), new Lambertian(vec3(0.4, 0.8, 0.4)));
    hitables.push_back(ground);
    std::cout << hitables.size() << std::endl;
    
    // pass hitables to world
    Hitable* world = new HitableList(hitables);

    for (int i = 0; i < scrWidth; i++)
    {
        for (int j = 0; j < scrHeight; j++)
        {
            Ray r;
            LightIntensity finalColor;
            
            finalColor.AddLightToCalculate(point);
            //finalColor = point.getDiffuse(vec3(0,0,0), vec3())

            float u = float(i) / float(scrWidth);
            float v = float(j) / float(scrHeight);

            float uMin = u - (pixelWidth / 2);
            float uMax = u + (pixelWidth / 2);

            float vMin = v - (pixelHeight / 2);
            float vMax = v + (pixelHeight / 2);

            if (isAntyalia == true)
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
