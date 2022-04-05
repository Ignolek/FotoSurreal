﻿#include <iostream>
#include <fstream>
#include "vec3.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "LightIntensity.h"
#include "HitableList.h"

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
    int scrWidth = 2000;
    int scrHeight = 1000;
    int depth = 1;

    Image* orthogonal = new Image(scrWidth, scrHeight, 3);
    Image* perspective = new Image(scrWidth, scrHeight, 3);

    LightIntensity lColor(220, 0, 0);
    Sphere sphere(vec3(0, 0, -1), 0.5);
    Hitable* list[3];
    list[0] = new Sphere(vec3(0.0, 0.0, -1), 0.25);
    list[1] = new Sphere(vec3(0, -100.5, -1), 100);
    list[2] = new Sphere(vec3(-0.25, 0, -4), 0.25);
    Hitable* world = new HitableList(list, 3);
    float fov = 45;
    Camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, -1, 0), fov, float(scrWidth)/float(scrHeight));
    bool ortho = true;

    float pixelWidth = 2 / scrWidth;
    float pixelHeight = 2 / scrHeight;
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

                    float uMin = (-1.f + i * pixelWidth) * (90 * (float(scrWidth) / float(scrHeight)));
                    float vMin = (1.f - (j + 1.0f) * pixelHeight) * 90;

                    float uMax = (-1.f + (i + 1.0f) * pixelWidth) * (90 * (float(scrWidth) / float(scrHeight)));
                    float vMax = (1.f - j * pixelHeight) * 90;

                    //LightIntensity color = GetColorByAntialiasing(world, uMin, uMax, vMin, vMax, i, j, 1.0f, vector<LightIntensity*>{nullptr, nullptr, nullptr, nullptr, nullptr});

                    float pixelCenterX = u + pixelWidth;
                    float pixelCenterY = v + pixelHeight;

                    if (ortho == true)
                    {
                        r = cam.getRay(u, v, fov, fov / 45, ortho);
                        col = color(r, world);
        
                        int iR = int(255.99 * col[0]);
                        int iG = int(255.99 * col[1]);
                        int iB = int(255.99 * col[2]);

                        lColor(iR, iG, iB);
                        orthogonal->SetPixel(i, j, lColor);
                    }

                    else
                    {
                        r = cam.getRay(u, v, fov, fov / 45, ortho);
                        col = color(r, world);

                        int iR = int(255.99 * col[0]);
                        int iG = int(255.99 * col[1]);
                        int iB = int(255.99 * col[2]);

                        lColor(iR, iG, iB);
                        perspective->SetPixel(i, j, lColor);
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
