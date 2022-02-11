// c++ version implemented from this video
// https://www.youtube.com/watch?v=MvlhMEE9zuc

// #include "helper.h"
#include <cmath>
#include <iostream>

using namespace std;

// Functional objects for the Seperate Axis Theorum (SAT)
// Single vertex
struct Point {
    float x;
    float y;
};

// The polygon that is formed from vertices and edges.
struct Polygon {
    Point vertex[4];
    Point edge[4];
};

struct Rectangle {
    float x;
    float y;
    float width;
    float height;
    float rotation;
} rectangle1, rectangle2;

struct Rotated {
    Point tl;
    Point tr;
    Point bl;
    Point br;
};

void printRectangleCoords(Rotated rectangle) {
    cout << "tl: " << "(" << rectangle.tl.x << ", " << rectangle.tl.y << ")" << endl;
    cout << "tr: " << "(" << rectangle.tr.x << ", " << rectangle.tr.y << ")" << endl;
    cout << "bl: " << "(" << rectangle.bl.x << ", " << rectangle.bl.y << ")" << endl;
    cout << "br: " << "(" << rectangle.br.x << ", " << rectangle.br.y << ")\n" << endl;
}

Point workOutNewPoints(float cx, float cy, float vx, float vy, float rotatedAngle) { //From a rotated object
    // cx,cy are the centre coordinates, vx,vy is the point to be measured against the center point
    // Convert rotated angle into radians

    rotatedAngle = rotatedAngle * M_PI / 180;
    float dx = vx - cx;
    float dy = vy - cy;
    float distance = sqrt(dx * dx + dy * dy);
    float originalAngle = atan2(dy,dx);
    float rotatedX = cx + distance * cos(originalAngle + rotatedAngle);
    float rotatedY = cy + distance * sin(originalAngle + rotatedAngle);

    struct Point p;
    p.x = rotatedX;
    p.y = rotatedY;
    return p;
}

// Get the rotated coordinates for the square
Rotated getRotatedSquareCoordinates(Rectangle square) {
    float centerX = square.x + (square.width / 2);
    float centerY = square.y + (square.height / 2);
    // Work out the new locations
    Point topLeft = workOutNewPoints(centerX, centerY, square.x, square.y, square.rotation);
    Point topRight = workOutNewPoints(centerX, centerY, square.x + square.width, square.y, square.rotation);
    Point bottomLeft = workOutNewPoints(centerX, centerY, square.x, square.y + square.height, square.rotation);
    Point bottomRight = workOutNewPoints(centerX, centerY, square.x + square.width, square.y + square.height, square.rotation);

    struct Rotated rotatedObject = {topLeft, topRight, bottomLeft, bottomRight};

    printRectangleCoords(rotatedObject);

    return rotatedObject;
}

// The actual Seperating Axis Theorum function
bool sat(Polygon polygonA, Polygon polygonB) {
    Point* perpendicularLine = NULL;
    float dot = 0;
    Point perpendicularStack[8]; // This only works for Rectangles
    float amin = -1234;  // TODO figure out how to make NULL?
    float amax = -1234;
    float bmin = -1234;
    float bmax = -1234;
    int NULL_VALUE = -1234;
    // Work out all perpendicular vectors on each edge for polygonA
    for (int i = 0; i < 4; i++)  // sizeof(polygonA.edge)
    {
        Point perpendicularLine = {-polygonA.edge[i].y,
                                    polygonA.edge[i].x};
        perpendicularStack[i] = perpendicularLine;
    }

    // Work out all perpendicular vectors on each edge for polygonB
    for (int i = 0; i < 4; i++)  // sizeof(polygonB.edge)
    {
        Point perpendicularLine = {-polygonB.edge[i].y,
                                    polygonB.edge[i].x};
        perpendicularStack[i+4] = perpendicularLine;
    }

    // Loop through each perpendicular vector for both polygons
    for (int i = 0; i < 8; i++)  // sizeof(perpendicularStack)
    {
        // These dot products will return different values each time
        amin = NULL_VALUE;
        amax = NULL_VALUE;
        bmin = NULL_VALUE;
        bmax = NULL_VALUE;

        /* Work out all of the dot products for all of the vertices in PolygonA against the perpendicular vector
         that is currently being looped through */
        for (int j = 0; j < 4; j++) // sizeof(polygonA.vertex)
        {
            dot = (polygonA.vertex[j].x * perpendicularStack[i].x) +
                  (polygonA.vertex[j].y * perpendicularStack[i].y);
        // Then find the dot products with the highest and lowest values from polygonA.
            if (amax == NULL_VALUE || dot > amax) {
                amax = dot;
            }
            if (amin == NULL_VALUE || dot < amin ) {
                amin = dot;
            }
        }
        /* Work out all of the dot products for all of the vertices in PolygonB against the perpendicular vector
         that is currently being looped through */
        for (int j = 0; j < 4; j++) {  // sizeof(polygonB.vertex)
            dot = (polygonB.vertex[j].x * perpendicularStack[i].x) +
                  (polygonB.vertex[j].y * perpendicularStack[i].y);
            // Then find the dot products with the highest and lowest values from polygonB.
            if (bmax == NULL_VALUE || dot > bmax) {
                bmax = dot;
            }
            if (bmin == NULL_VALUE || dot < bmin) {
                bmin = dot;
            }
        }
        // If there is no gap between the dot products projection then we will continue onto evaluating the next perpendicular edge.
        if ((amin < bmax && amin > bmin) || (bmin < amax && bmin > amin)) {
            continue;
        }
        // Otherwise, we know that there is no collision for definite.
        else {
            return false;
        }
    }
    /* If we have gotten this far. Where we have looped through all of the perpendicular edges and not a single one of there projections had
    a gap in them. Then we know that the 2 polygons are colliding for definite then. */
    return true;
}

bool detectRectangleCollision(Rectangle thisRect, Rectangle otherRect) {

    Rotated tRR = getRotatedSquareCoordinates(thisRect);
    Rotated oRR = getRotatedSquareCoordinates(otherRect);

    struct Polygon thisRectPolygon = { 
        {
            {tRR.tr.x, tRR.tr.y},  // top-right
            {tRR.br.x, tRR.br.y},  // bottom-right
            {tRR.bl.x, tRR.bl.y},  // bottom-left
            {tRR.tl.x, tRR.tl.y}   // top-left
        },
        {
            {tRR.br.x - tRR.tr.x, tRR.br.y - tRR.tr.y},
            {tRR.bl.x - tRR.br.x, tRR.bl.y - tRR.br.y},
            {tRR.tl.x - tRR.bl.x, tRR.tl.y - tRR.bl.y},
            {tRR.tr.x - tRR.tl.x, tRR.tr.y - tRR.tl.y}
        }
    };

    struct Polygon otherRectPolygon = {
        {
            {oRR.tr.x, oRR.tr.y},
            {oRR.br.x, oRR.br.y},
            {oRR.bl.x, oRR.bl.y},
            {oRR.tl.x, oRR.tl.y}
        },
        {
            {oRR.br.x - oRR.tr.x, oRR.br.y - oRR.tr.y},
            {oRR.bl.x - oRR.br.x, oRR.bl.y - oRR.br.y},
            {oRR.tl.x - oRR.bl.x, oRR.tl.y - oRR.bl.y},
            {oRR.tr.x - oRR.tl.x, oRR.tr.y - oRR.tl.y}
        }
    };

    if (sat(thisRectPolygon, otherRectPolygon)) {
        return true;
    } else {
        // Because we are working with vertices and edges. This algorithm does not cover the normal un-rotated rectangle
        // algorithm which just deals with sides
        if (thisRect.rotation == 0 && otherRect.rotation == 0)
        {
            if (!(
                thisRect.x > otherRect.x + otherRect.width || 
                thisRect.x + thisRect.width < otherRect.x || 
                thisRect.y > otherRect.y + otherRect.height || 
                thisRect.y + thisRect.height < otherRect.y
            )){
                return true;
            } 
        }
        return false;
        
    }
}

int main()
{   
    // rectangle1
    rectangle1.x = 0;
    rectangle1.y = 0;
    rectangle1.width = 100;
    rectangle1.height = 100;
    rectangle1.rotation = 0;
    // rectangle2
    /*rectangle2.x = 20;
    rectangle2.y = 20;
    rectangle2.width = 100;
    rectangle2.height = 100;
    rectangle2.rotation = 1;*/
    rectangle2.x = 0;
    rectangle2.y = 0;
    rectangle2.width = 100;
    rectangle2.height = 100;
    rectangle2.rotation = 1;

    if (detectRectangleCollision(rectangle1, rectangle2)) {
        cout << "COLLISION!";
    } else {
        cout << "NO COLLISION!";
    }

    return 0;
}

/*
list types = 
    1. Wall things
        - book shelves
        - pictures
        - lights
    2. random in room
    2. floor things
        - like rugs, that don't matter if it "intersects"

ALGORITHM:
    for item in each of the list types:
        for i in range(10)
            try to place object


Separating Axis Theory
https://www.gamedev.net/tutorials/_/technical/game-programming/2d-rotated-rectangle-collision-r2604/
*/
