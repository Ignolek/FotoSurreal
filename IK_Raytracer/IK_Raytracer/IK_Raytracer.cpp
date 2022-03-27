#include <iostream>
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Image.h"
#include "Camera.h"
#include "LightIntensity.h"

int main()
{
   /* Vector v1(1, 1, 1);
    Vector v2(200, 300, 400);
    Vector v4(100, 100, 100);
    Vector* defaultVector = new Vector();
    Vector* definedVector = new Vector(150.5, 222.0, 321.55);
    Vector* v3 = new Vector(*definedVector);
    Vector* definedVector2 = new Vector(*defaultVector, *definedVector);
    std::cout << "Default Vector constructor has made: " + defaultVector->toString() << std::endl;
    std::cout << "Defined Vector constructor has made: " + definedVector->toString() << std::endl;
    std::cout << "Defined Vector2 constructor has made: " + definedVector2->toString() << std::endl;
    std::cout << "Default Vector constructor has made: " + defaultVector->toString() << std::endl;*/

    //2. Zdefiniować sferę S o środku w punkcie (0,0,0) i promieniu 10.
    //Sphere S(Vector(0, 0, 0), 10);

    //3. Zdefiniować promień R1 o początku w punkcie(0, 0, -20) i skierowany w środek kuli.
    //Ray R1(Vector(0, 0, -20), Vector(0, 0, 20));

    //4. Zdefiniować promień R2 o początku w tym samym punkcie, co R1, skierowany równolegle do osi Y. ??
    //Ray R2(Vector(0, 0, -20), Vector(0, 1, 0));

    //5. Proszę sprawdzić, czy istnieje przecięcie sfery S z promieniami R1 oraz R2. Wynik w postaci współrzędnych punktu przecięcia należy wyświetlić.
    //std::cout << S.intersect(R1)[0] << std::endl;
    //std::cout << S.intersect(R1)[1] << std::endl;

    //std::cout << S.intersect(R2)[0] << std::endl;
    //std::cout << S.intersect(R2)[1] << std::endl;

    //6. Proszę zdefiniować dowolny promień R3, tak aby przecinał on sferę S w dokładnie jednym punkcie.Podać współrzędne punktu przecięcia.

    //Ray R3(Vector(0, 0, -20), Vector(0, 2.88676, 5));

    //std::cout << S.intersect(R3)[0] << std::endl;
    //std::cout << S.intersect(R3)[1] << std::endl;

    //7. Prosze zdefiniować płaszczyznę P przechodzącą przez punkt (0, 0, 0),
    //której wektor normalny tworzy kąt 45 stopni z osiami Y i Z
    //Plane P1(0, 1, 1, 0);

    //8. Proszę znaleźć punkt przecięcia płaszczyzny P z promieniem R2
    //std::cout << P1.intersectLine(R2.getOrigin(), R2.getDirection()).toString();

    int scrWidth = 500;
    int scrHeight = 500;
    Image* blank = new Image(scrWidth, scrHeight, 3);
    blank->FillColor(0, 0, 0);

    // Engine objects
    Camera* cam = new Camera();
    Sphere* sphere = new Sphere(Vector(240.0f, 240.0f, 2.0f), 35.5f);
    LightIntensity* sphereColor = new LightIntensity(250, 0, 0);
    LightIntensity* backgroundColor = new LightIntensity(50, 50, 150);


    for (int x = 0; x < scrWidth; x++)
    {
        for (int y = 0; y < scrHeight; y++)
        {
            Ray ray = cam->render(scrWidth, scrHeight, x, y, 2.0f);
            //Vector* intersection = sphere->intersect(ray); //nullptr;
            //intersection = sphere->intersect(ray);
            //Ray ray(Vector(x, y, 0), Vector(0, 0, 1));

            if (sphere->hitRay(ray))
            {
                blank->SetPixel(x, y, *sphereColor);
            }
            else
            {
                blank->SetPixel(x, y, *backgroundColor);
            }
        }
    }
    blank->Write("obrazek.png");

    return 0;
}
