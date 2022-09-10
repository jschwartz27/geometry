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
};

struct Rotated {
    Point tl;
    Point tr;
    Point bl;  // switched bl, br and tl tr
    Point br;
};


// UE4 Stuff
struct FVector {
    float X;
    float Y;
    float Z;
};

struct FRotator {
    float Pitch;
    float Yaw;
    float Roll;
};

struct FTransform {
    FVector location;
    FRotator rotation;
    FVector scale = {1.f, 1.f, 1.f};
};