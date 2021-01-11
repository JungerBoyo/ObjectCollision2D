#include "../headers/X11WindowManager.h"
#include "../headers/Geometry.h"
#include <vector>
#include <iostream>

float TransformForward(Shape& shape, vec2& a) //a1/a2
{  
    float y = sqrt(10/((a.Y * a.Y)/(a.X * a.X)+1));
    float x = (a.Y*y)/a.X;

    vec2 diff = shape.data.Points[0] - shape.data.center;

    y = (diff.Y > 0) ? y : -y;
    x = (diff.X > 0) ? x : -x; 

    y = (a.X/a.Y > 0) ? y : -y;
    x = (a.X/a.Y > 0) ? x : -x;

    std::cout << diff.X << " " << diff.Y << "\n";
    std::cout << x << " " << y << "\n";

    shape.data.center += vec2(x, y);

    for(int i=0; i<shape.data.Points.size(); i++)
        shape.data.Points[i] += vec2(x, y);
    
    return a.X/a.Y;
}

vec2 Rot(Shape& shape, const rotmat2x2& mat2)
{
    for(int i=0; i<shape.data.Points.size(); i++)
    {
        shape.data.Points[i] = vec2((mat2.mat[0] * (shape.data.Points[i].X-shape.data.center.X) + mat2.mat[1] *  (shape.data.Points[i].Y-shape.data.center.Y)) + shape.data.center.X ,
                                    (mat2.mat[2] * (shape.data.Points[i].X-shape.data.center.X) + mat2.mat[3] *  (shape.data.Points[i].Y-shape.data.center.Y)) + shape.data.center.Y);
    }

    return vec2((shape.data.center.Y - shape.data.Points[0].Y), (shape.data.center.X - shape.data.Points[0].X));
}


int main()
{
    XEvent event;
    KeySym key;
    char text[255];

    X11WindowManager* X11panel = new X11WindowManager(true);
    
    Shape* Triangle = new Shape(PENTAGON, vec2(250.0f, 250.0f), 50.0f); 
    vec2 a = vec2(1,1);
    X11panel -> DrawPolygon(*Triangle, "gray0");

    while(true)
    {
       XNextEvent(X11panel->Dis(), &event);

       if(event.type == ButtonPress)
       {
           X11panel -> DrawPolygon(*Triangle, "gray0");

           std::cout << event.xbutton.x << "  " << event.xbutton.y << '\n';
       }
       else if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key,  0) == 1)
       {
           XClearWindow(X11panel->Dis(), X11panel->Win());

           switch(text[0])
           {
               case 'w': std::cout << TransformForward(*Triangle, a) << "\n"; break;
               case 'e': a = Rot(*Triangle, rotmat2x2(pi/90)); break;
               case 'q': a = Rot(*Triangle, rotmat2x2(pi/-90)); break;
               default: break;
           }

           X11panel -> DrawPolygon(*Triangle, "gray0");
       }
    }

    return 0;
}