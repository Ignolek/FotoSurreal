#include <iostream>
#include "Vector.h"

int main()
{
    Vector* defaultVector = new Vector();
    Vector* definedVector = new Vector(150.5, 222.0, 321.55);
    Vector* definedVector2 = new Vector(*defaultVector, *definedVector);
    std::cout << "Default Vector constructor has made: " + defaultVector->toString() << std::endl;
    std::cout << "Defined Vector constructor has made: " + definedVector->toString() << std::endl;
    std::cout << "Defined Vector2 constructor has made: " + definedVector2->toString() << std::endl;

}
