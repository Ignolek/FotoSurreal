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

    Image* blank = new Image(scrWidth, scrHeight, 3);

    LightIntensity lColor(220, 0, 0);
    Sphere sphere(vec3(0, 0, -1), 0.5);
    Hitable* list[3];
    list[0] = new Sphere(vec3(0.5, 0, -1), 0.25);
    list[1] = new Sphere(vec3(0, -100.5, -1), 100);
    list[2] = new Sphere(vec3(-0.5, 0, -4), 0.25);
    Hitable* world = new HitableList(list, 3);
    Camera cam(vec3(0, 0, 0), vec3(0.0, 0, -1), vec3(0, -1, 0), 90, float(scrWidth)/float(scrHeight));
    bool ortho = false;
    std::cout << "Do You want to use orthogonal camera? [0 -- no, 1 -- yes]: ";
    std::cin >> ortho;

    float pixelWidth = 2.0f / scrWidth;
    float pixelHeight = 2.0f / scrHeight;

    for (int i = 0; i < scrWidth; i++)
    {
        for (int j = 0; j < scrHeight; j++)
        {
            vec3 col(0, 0, 0);
            for (int s = 0; s < depth; s++)
            {
                float u = float(i) / float(scrWidth);
                float v = float(j) / float(scrHeight);

                float pixelCenterX = -1.0f + (i + 0.5f) * u;
                float pixelCenterY = 1.0f - (j + 0.5f) * v;

                Ray r = cam.getRay(u, v, ortho);
                col += color(r, world);
            }
           
            col /= float(depth);

            int iR = int(255.99 * col[0]);
            int iG = int(255.99 * col[1]);
            int iB = int(255.99 * col[2]);

            lColor(iR, iG, iB);
            blank->SetPixel(i, j, lColor);
        }
    }
    blank->Write("obrazek.bmp");

    return 0;
}
