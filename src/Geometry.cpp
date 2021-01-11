#include "../headers/Geometry.h"

Shape::Shape(const polygonType _type, vec2 _centerPoint, float _scale)
{
    switch(_type)
    {
        case TRIANGLE: CreateTriangle(_centerPoint, _scale); break;
        case RECTANGLE: CreateRectangle(_centerPoint, _scale); break;
        case PENTAGON: CreatePentagon(_centerPoint, _scale); break;
    }
}

void Shape::CreateTriangle(vec2 _centerPoint, float _scale)
{
    data.angle = (2*pi)/3;
    data.center = _centerPoint;
    data.scale = _scale;
    float ang = 0;

    for(int i=0; i<3; i++)
    {
        data.OriginPoints.push_back(vec2( (_scale)*cos(ang)+_centerPoint.X + (_scale)*sin(ang)+_centerPoint.Y, 
                                         -(_scale)*sin(ang)+_centerPoint.X + (_scale)*cos(ang)+_centerPoint.Y)); 
                                            // vec2[ xcosx + ysinx , -xcosx + ysinx ]
    
        data.Points.push_back(data.OriginPoints.back());
        ang += data.angle;
    }
}

void Shape::CreateRectangle(vec2 _centerPoint, float _scale)
{
    data.angle = (2*pi)/4;
    data.center = _centerPoint;
    data.scale = _scale;
    float ang = 0;

    for(int i=0; i<4; i++)
    {
        data.OriginPoints.push_back(vec2( (_scale)*cos(ang)+_centerPoint.X + (_scale)*sin(ang)+_centerPoint.Y, 
                                         -(_scale)*sin(ang)+_centerPoint.X + (_scale)*cos(ang)+_centerPoint.Y)); 
                                            // vec2[ xcosx + ysinx , -xcosx + ysinx ]
    
        data.Points.push_back(data.OriginPoints.back());
        ang += data.angle;
    }
}

void Shape::CreatePentagon(vec2 _centerPoint, float _scale)
{
    data.angle = (2*pi)/5;
    data.center = _centerPoint;
    data.scale = _scale;
    float ang = 0;

    for(int i=0; i<5; i++)
    {
        data.OriginPoints.push_back(vec2( ((_scale)*cos(ang) + (_scale)*sin(ang))+_centerPoint.X, 
                                         (-(_scale)*sin(ang) + (_scale)*cos(ang))+_centerPoint.Y)); 
                                            // vec2[ xcosx + ysinx , -xcosx + ysinx ]
    
        data.Points.push_back(data.OriginPoints.back());
        ang += data.angle;
    }
}