#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include <math.h>

#define pi 3.14159265

struct vec2
{
    vec2(float x = 0, float y = 0)
    {
        X = x;
        Y = y;
    }

    float X;
    float Y;
};

struct polygon 
{
    std::vector<vec2> OriginPoints;
    std::vector<vec2> Points;
    vec2 center;
    float angle;
    float scale;
    //bool isCovered? 
};

inline vec2 operator+(vec2 const& v1, vec2 const& v2)
{
    return vec2(v1.X+v2.X, v1.Y+v2.Y);
}

enum polygonType
{
    TRIANGLE,
    RECTANGLE,
    PENTAGON
};

class Shape
{
    public:
        Shape(const polygonType type, vec2 centerPoint, float scale);

        polygon data;

        
 
    private:
        void CreateTriangle(vec2 centerPoint, float scale);
        void CreateRectangle(vec2 centerPoint, float scale);
        void CreatePentagon(vec2 centerPoint, float scale);
};

#endif