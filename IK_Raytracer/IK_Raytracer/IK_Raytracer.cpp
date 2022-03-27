#include <iostream>
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "LightIntensity.h"
#include "vec3.h"

vec3 color(const Ray& r)
{
    vec3 unitDirection = unit_vector(r.direction());
    float t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
  
    int scrWidth = 200;
    int scrHeight = 100;
    vec3 lowerLefrCorner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    Image* blank = new Image(scrWidth, scrHeight, 3);

    LightIntensity lColor(220, 0, 0);

    for (int j = scrHeight - 1; j >= 0; j--)
    {
        for (int i = 0; i < scrWidth; i++)
        {
            float u = float(i) / float(scrWidth);
            float v = float(j) / float(scrHeight);

            Ray r(origin, lowerLefrCorner + u * horizontal + v * vertical);
            vec3 col = color(r);

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
