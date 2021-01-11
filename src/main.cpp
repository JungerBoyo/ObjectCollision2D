#include "../headers/X11WindowManager.h"
#include "../headers/Geometry.h"
#include <vector>
#include <iostream>

void TransformForward(Shape& shape)
{
    float a = (shape.data.center.Y - shape.data.Points[0].Y) / (shape.data.center.X - shape.data.Points[0].X);
    float b;

    b = shape.data.center.Y - a*shape.data.center.X;
    shape.data.center = vec2((shape.data.center.Y+2.0f - b)*a,a*(shape.data.center.X+2.0f) + b);

    for(int i=0; i<shape.data.Points.size(); i++)
    {
        b = shape.data.Points[i].Y - a*shape.data.Points[i].X;
        shape.data.Points[i] = vec2((shape.data.Points[i].Y+2.0f - b)*a,a*(shape.data.Points[i].X+2.0f) + b);
    }
}

int main()
{
    XEvent event;
    KeySym key;
    char text[255];

    X11WindowManager* X11panel = new X11WindowManager(true);
    
    Shape* Triangle = new Shape(PENTAGON, vec2(250.0f, 250.0f), 50.0f); 

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
               case 'w': TransformForward(*Triangle); break;
               case 'e': //RotRight(Triangle); break;
               case 'q': //RotLeft(Triangle); break;
               default: break;
           }

           X11panel -> DrawPolygon(*Triangle, "gray0");
       }
    }

    return 0;
}