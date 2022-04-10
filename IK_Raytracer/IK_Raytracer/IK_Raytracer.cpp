#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "LightIntensity.h"
#include "HitableList.h"
#include "ObjParser.h"

vec3 color(const Ray& r, Hitable *world)
{
    hitRecord rec;
    if (world->hit(r, 0.0, FLT_MAX, rec) == true)
    {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    }
    else 
    {
        vec3 unitDirection = unit_vector(r.direction());
        float t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int scrWidth = 200;
    int scrHeight = 100;
    int depth = 1;

    Image* orthogonal = new Image(scrWidth, scrHeight, 3);
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    ObjParser parser;
    std::vector<vec3> vertices, indices;
    parser.ParseFile("Cone.obj", vertices, indices);
    //std::cout << finalColor.getRed() << "  " << finalColor.getGreen() << "  " << finalColor.getBlue() << std::endl;

    LightIntensity testColor(100, 100, 100);
    LightIntensity* testColor2 = new LightIntensity(120, 120, 120);
    testColor += *testColor2;
    //if (*testColor == *testColor2)
    //{
        std::cout << testColor.getRed() << "  " << testColor.getGreen() << "  " << testColor.getBlue() << std::endl;
    //}
    

    LightIntensity lColor(220, 0, 0);

    Hitable* list[3];
    list[0] = new Sphere(vec3(0.0, 0.0, -1.25), 0.25, vec3(255, 0, 0));
    list[1] = new Sphere(vec3(0, -100.5, -1), 100, vec3(0, 255, 0));
    list[2] = new Sphere(vec3(-0.25, 0, -4), 0.25, vec3(0, 0, 255));
    Hitable* world = new HitableList(list, 3);
    float fov = 90;
    //Camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));
    Camera* cam = new Camera(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));
    bool ortho = true;

    float pixelWidth = 2.0f / scrWidth; // 0.01
    float pixelHeight = 2.0f / scrHeight; // 0.0

    //std::cout << pixelWidth << ", " << pixelHeight << std::endl;
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
                vec3 col(0, 0, 0);
                Ray r;
                for (int s = 0; s < depth; s++)
                {
                    float u = float(i) / float(scrWidth);
                    float v = float(j) / float(scrHeight);

                    float uMin = u - (pixelWidth / 2);
                    float uMax = u + (pixelWidth / 2);

                    float vMin = v - (pixelHeight / 2); 
                    float vMax = v + (pixelHeight / 2);

                    if (uMin < 0) uMin = 0;
                    if (vMin < 0) vMin = 0;
                    if (uMax > 1) uMax = 1;
                    if (vMax > 1) vMax = 1;

                    /*float uMin = (-1.f + (i * pixelWidth)) * (fov * float(scrWidth) / float(scrHeight));
                    float uMax = (-1.f + ((i + 1.0f) * pixelWidth)) * (fov * float(scrWidth) / float(scrHeight));

                    float vMax = (1.0f - (j * pixelHeight)) * fov;
                    float vMin = (1.0f - ((j + 1.0f) * pixelHeight)) * fov;*/




                   /*std::cout << "[" << i << ", " << j << "]: " << "UV: [" << u << ", " << v << "]: "
                              << "uMinMax: [" << uMin << ", " << uMax << "]" << "vMinMax: [" << vMin << ", " << vMax << "]" << std::endl;*/

                    LightIntensity finalColor = finalColor.Antialiasing(world, cam, fov, fov / 45, ortho, 
                                                                        uMin, uMax, vMin, vMax, i, j, 2, 
                                                                        std::vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr});
                    
                    float pixelCenterX = u + pixelWidth;
                    float pixelCenterY = v + pixelHeight;

                    if (ortho == true)
                    {
                        r = cam->getRay(u, v, fov, fov / 45, ortho);
                        //col = color(r, world);
                        LightIntensity newColor = newColor.GetColorFromRay(r, world);
                        //int iR = int(255.99 * newColor.getRed());
                        //int iG = int(255.99 * newColor.getGreen());
                        //int iB = int(255.99 * newColor.getBlue());

                        //lColor(iR, iG, iB);
                        orthogonal->SetPixel(i, j, finalColor);
                    }

                    else
                    {
                        r = cam->getRay(u, v, fov, fov / 45, ortho);
                        //col = color(r, world);
                        LightIntensity newColor = newColor.GetColorFromRay(r, world);
                        //int iR = int(255.99 * newColor.getRed());
                        //int iG = int(255.99 * newColor.getGreen());
                        //int iB = int(255.99 * newColor.getBlue());

                        //lColor(iR, iG, iB);
                        perspective->SetPixel(i, j, finalColor);
                    }
                }
            }
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
