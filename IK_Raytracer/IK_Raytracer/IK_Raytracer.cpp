﻿#include <iostream>
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
    int scrWidth = 1920 / 4;
    int scrHeight = 1080 / 4;
    int deepth = 100;
    vec3 lowerLefrCorner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    Image* blank = new Image(scrWidth, scrHeight, 3);

    LightIntensity lColor(220, 0, 0);
    Sphere sphere(vec3(0, 0, -1), 0.5);


    Hitable* list[3];
    list[0] = new Sphere(vec3(0.3, 0, -1), 0.5);
    list[1] = new Sphere(vec3(0, -100.5, -1), 100);
    list[2] = new Sphere(vec3(0, 0, -0.8), 0.3);
    //list[2] = new Plane(vec3(0, 0, -1), vec3(0.2, 0.3, -1), vec3(0.3, 0.3, -1));
    // 
    //list[1] = new Plane(1,0,1,-1);
    //list[2] = new Plane(0, 2, 1, -1);
    //list[3] = new Plane(-1, 0, 1, -1);
    //list[4] = new Plane(0, -2, 1, -1);
    Hitable* world = new HitableList(list, 3);
    Camera cam;

    for (int j = -(scrHeight / 2); j < scrHeight / 2; j++)
    {
        for (int i = -(scrWidth / 2); i < scrWidth / 2; i++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < deepth; s++)
            {
                float u = float(i) / float(scrWidth);
                float v = float(j) / float(scrHeight);
                Ray r = cam.getRay(u, v);
                vec3 p = r.pointAtParameter(2.0);
                col += color(r, world);
            }
           
            col /= float(deepth);

            int iR = int(255.99 * col[0]);
            int iG = int(255.99 * col[1]);
            int iB = int(255.99 * col[2]);

            lColor(iR, iG, iB);
            
            blank->SetPixel(i, j, lColor);
        }
    }
     
    //for (int j = -(scrHeight / 2); j < scrHeight / 2; j++)
    //{
    //    for (int i = -(scrWidth / 2); i < scrWidth / 2; i++)
    //    {
    //        blank->SetPixel(i, j, LightIntensity(100, 50, 200));
    //    }
    //}
    //blank->FillColor(LightIntensity(100, 50, 200));

    blank->Write("obrazek.bmp");

    return 0;
}
