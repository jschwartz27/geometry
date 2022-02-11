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
    Point bl;  // switched bl, br and tl tr
    Point br;
    
};
