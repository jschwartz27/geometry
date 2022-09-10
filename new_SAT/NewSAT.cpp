// c++ version implemented from this video
// https://www.youtube.com/watch?v=MvlhMEE9zuc

#include "NewSAT.h"
#include <cmath>
#include <iostream>
using namespace std;

Vector GetVectorFromCoords(Vector C1, Vector C2)
{
    // ​To calculate a vector that points from coordinate one to coordinate two
    return {
        C2.x - C1.x,
        C2.y - C1.y
    };
}

Vector GetPerpindicularVector(Vector vector)
{
    // To calculate a perpendicular vector, swap the x and y components,
    // then negate the x components
    return {
        -vector.y,
        vector.x
    };
}

float DotProduct(Vector V1, Vector V2)
{
    /* The product of the x component of the first vector and the x component of the
    second vector summed with the product of the y component of the first vector and
    the y component of the second vector */
    return (V1.x * V2.x) + (V1.y * V2.y);
}