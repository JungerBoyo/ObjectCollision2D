#include "../headers/Geometry.h"

Shape::Shape(const polygonType _type, vec2 _centerPoint, float _scale)
{
    switch(_type)
    {
        case TRIANGLE: CreatePolygon(TRIANGLE, _centerPoint, _scale); break;
        case RECTANGLE: CreatePolygon(RECTANGLE, _centerPoint, _scale); break;
        case PENTAGON: CreatePolygon(PENTAGON, _centerPoint, _scale); break;
        case NONAGON: CreatePolygon(NONAGON, _centerPoint, _scale); break;
        case RANDOM: CreateRandomPolygon(RANDOM,  _centerPoint, _scale); break;
    }
}

void Shape::CreatePolygon(polygonType _type, vec2 _centerPoint, float _scale)
{
    data.angle = (2*pi)/_type;
    data.center = _centerPoint;
    data.scale = _scale;
    data.Count = _type;
    float ang = 0;

    for(int i=0; i<_type; i++)
    {
        data.OriginPoints.push_back(vec2( ((_scale)*cos(ang) + (_scale)*sin(ang))+_centerPoint.X, 
                                         (-(_scale)*sin(ang) + (_scale)*cos(ang))+_centerPoint.Y)); 
                                            // vec2[ xcosx + ysinx , -xcosx + ysinx ]
    
        data.Points.push_back(data.OriginPoints.back());
        ang += data.angle;
    }
}

void Shape::CreateRandomPolygon(polygonType _type, vec2 _centerPoint, float _scale)
{
    data.Count = rand()%10+5;
    data.angle = (2*pi)/data.Count;
    data.center = _centerPoint;
    data.scale = RANDOM;

    float ang = 0;

    for(int i=0; i<data.Count; i++)
    {
        data.OriginPoints.push_back(vec2( ((rand()%25+50)*cos(ang) + (rand()%25+50)*sin(ang))+_centerPoint.X, 
                                         (-(rand()%25+50)*sin(ang) + (rand()%25+50)*cos(ang))+_centerPoint.Y)); 
    
        data.Points.push_back(data.OriginPoints.back());
        ang += data.angle;
    }
}