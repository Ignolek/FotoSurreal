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

//vec3 color(const Ray& r, Hitable *world)
//{
//    hitRecord rec;
//    if (world->hit(r, 0.0, FLT_MAX, rec) == true)
//    {
//        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
//    }
//    else 
//    {
//        vec3 unitDirection = unit_vector(r.direction());
//        float t = 0.5 * (unitDirection.y() + 1.0);
//        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
//    }
//}

int main()
{
    int scrWidth = 1000;
    int scrHeight = 500;

    bool isAntyalia = true;

    std::cout << "Do you want to turn on antyaliasing [0 -- no, 1 -- yes]?: ";
    std::cin >> isAntyalia;
    Image* orthogonal = new Image(scrWidth, scrHeight, 3);
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    ObjParser parser;
    std::vector<vec3> vertices, indices;
    parser.ParseFile("cubeTri.obj", vertices, indices);
    float scale = 1 / 2.0f;
  
    // vector of hitable objects
    std::vector<Hitable*> hitables;
    
    Hitable* list[4];
    list[0] = new Triangle(vec3(-1.2, 0.0, -0.2), vec3(0.2, 0.0, -0.2), vec3(0.0, 0.5, -0.2), vec3(0, 0, 0));
    list[1] = new Sphere(vec3(0.0, 0.0, -1), 0.25,vec3(255.0,161.0,0.0));
    list[2] = new Sphere(vec3(0, -100.5, -1), 100, vec3(0, 154, 23));
    list[3] = new Sphere(vec3(-0.25, 0, -0.5), 0.35, vec3(201.0, 118.0, 11.0));

    // for loop which iterates through all vertices in parser
    for (int i = 0; i < indices.size(); i++)
    {
        // Triangle made from indices 
        Hitable* meshTriangle = new Triangle(vertices.at(indices.at(i).x()) * scale - vec3(0, 0, 0), 
                                             vertices.at(indices.at(i).y()) * scale - vec3(0, 0, 0),
                                             vertices.at(indices.at(i).z()) * scale - vec3(0, 0, 0),
                                             vec3(200, 50, 50));
      

       /* std::cout << indices.at(i).x() << "/" << indices.at(i).y() << "/" << indices.at(i).z() 
                  << ":[" << vertices.at(indices.at(i).x()) << " / " 
                  << vertices.at(indices.at(i).y()) << " / "
                  << vertices.at(indices.at(i).z()) << "] " << std::endl;*/
        
        // Add triangle to hitables
        hitables.push_back(meshTriangle);
    }

    /*for (int i = 0; i < 4; i++)
        hitables.push_back(list[i]);*/
    hitables.push_back(list[2]);
    std::cout << hitables.size() << std::endl;
    
    // pass hitables to world
    Hitable* world = new HitableList(hitables);
    float fov = 45.0f;
    Camera* cam = new Camera(vec3(0, 0, 10), vec3(0, 0, -1000), vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));

    bool ortho = true;

    float pixelWidth = 2.0f / float(scrWidth);
    float pixelHeight = 2.0f / float(scrHeight); 

    for (int imageNumber = 0; imageNumber < 2; imageNumber++)
    {
        if (ortho == true)
            std::cout << "Orthogonal image is rendering now..." << std::endl;
        else
            std::cout << "Perspective image is rendering now..." << std::endl;
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

                /*if (uMin < 0) uMin = 0;
                if (vMin < 0) vMin = 0;
                if (uMax > 1) uMax = 1;
                if (vMax > 1) vMax = 1;*/

                if (isAntyalia)
                finalColor = finalColor.Antialiasing(world, cam, fov, fov / 45.0f, ortho, 
                                                                    uMin, uMax, vMin, vMax, i, j, 0.50f, 
                                                                    std::vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr});
                 
                
                float pixelCenterX = u + pixelWidth;
                float pixelCenterY = v + pixelHeight;

                if (ortho == true)
                {
                    if (isAntyalia == false)
                    {
                        r = cam->getRay(u, v, fov, fov / 45, ortho);
                        LightIntensity newColor = newColor.GetColorFromRay(r, world);

                        orthogonal->SetPixel(i, j, newColor);
                    }
                    else
                        orthogonal->SetPixel(i, j, finalColor);
                }

                else
                {
                    if (isAntyalia == false)
                    {
                        r = cam->getRay(u, v, fov, fov / 45, ortho);
                        LightIntensity newColor = finalColor.GetColorFromRay(r, world);

                        perspective->SetPixel(i, j, newColor);
                    }

                    else
                        perspective->SetPixel(i, j, finalColor);
                }
            }

            std::cout << "Please wait, " << (i * 100) / scrWidth << "% of image has been calculated." << std::endl;
        }
        orthogonal->Write("ortho.png");
        if(ortho == true)
            std::cout << "Orthogonal image created!" << std::endl;

        ortho = false;
    }

    perspective->Write("perspective.png");
    std::cout << "Pespective image created!" << std::endl;

    return 0;
}
