
#include "transformWallCoords.h"
#include <iostream>
#include <math.h>
using namespace std;

float roundDegree(float degree)
{
    return round(degree * 100000) / 100000;
}

Coord multiply(int m1, int m2, float coordMatrix[][2], int n1, int n2, float rotationMatrix[][2])
{
    int x, i, j;
    float res[m1][n2];
    float theDegree;
    float xCoord, yCoord;

    for (i = 0; i < m1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            res[i][j] = 0;
            for (x = 0; x < m2; x++)
            {
                *(*(res + i) + j) += *(*(coordMatrix + i) + x)
                                     * *(*(rotationMatrix + x) + j);
            }
        }
    }
    for (i = 0; i < m1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            
            if (j == 0)
            {    
                xCoord = roundDegree(*(*(res + i) + j));
                cout << "X" << " " << xCoord << " ";
            } else
            {
                yCoord = roundDegree(*(*(res + i) + j));
                cout << "Y" << " " << yCoord << " ";
            }
            
        }
    }
    return { xCoord, yCoord };
}

Coord rotateCoord(FVector coord, float rotationDegree)
{
    float PI = 3.14159265;

    float rotationMatrix[][2] = {
        { cos(rotationDegree*PI/180.f), sin(rotationDegree*PI/180.f) },
        { -sin(rotationDegree*PI/180.f), cos(rotationDegree*PI/180.f) }
    };

    float coordMatrix[][2] = {
        { coord.X, coord.Y }
    };

    return multiply(1, 2, coordMatrix, 2, 2, rotationMatrix);
}

FVector transformCoord(FVector coord, float rotationDegree)
{
    rotateCoord(coord, rotationDegree);
    return {
        1.f,
        2.f,
        0.f
    };
}

int main()
{
    struct FVector testCoord = {
        0.f,
        5.f,
        0.f
    };

    float rotationDegree = 270.f;

    FVector newCoord = transformCoord(testCoord, rotationDegree);

    return 0;
}