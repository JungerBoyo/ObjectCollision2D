#include "../headers/X11WindowManager.h"
#include "../headers/Geometry.h"
#include <vector>
#include <iostream>

int Transform(Shape& shape, vec2& a, const short dir, float dist) //a1/a2
{  
    float y = sqrt(dist/((a.Y * a.Y)/(a.X * a.X)+1));
    float x = (a.Y*y)/a.X;

    vec2 diff = shape.data.Points[0] - shape.data.center;

    y = (diff.Y > 0) ? y : -y;
    x = (diff.X > 0) ? x : -x; 
    x = (a.X/a.Y < 0) ? -x : x;

    shape.data.center += vec2(dir*x, dir*y);

    for(int i=0; i<shape.data.Count; i++)
        shape.data.Points[i] += vec2(dir*x, dir*y);

    return dir;
}

vec2 Rot(Shape& shape, const rotmat2x2& mat2)
{
    for(int i=0; i<shape.data.Count; i++)
    {
        shape.data.Points[i] = vec2((mat2.mat[0] * (shape.data.Points[i].X-shape.data.center.X) + mat2.mat[1] *  (shape.data.Points[i].Y-shape.data.center.Y)) + shape.data.center.X ,
                                    (mat2.mat[2] * (shape.data.Points[i].X-shape.data.center.X) + mat2.mat[3] *  (shape.data.Points[i].Y-shape.data.center.Y)) + shape.data.center.Y);
    }

    return vec2((shape.data.center.Y - shape.data.Points[0].Y), (shape.data.center.X - shape.data.Points[0].X));
}

bool checkCollision(Shape& sh1, Shape& sh2)
{
    for(int i=0; i<sh1.data.Count; i++)
    {
        float dx = sh1.data.Points[i].Y - sh1.data.Points[(i+1)%sh1.data.Count].Y;
        float dy =-(sh1.data.Points[i].X - sh1.data.Points[(i+1)%sh1.data.Count].X);

        float maxSh1 =-INFINITY;
        float minSh1 = INFINITY;
        for(int k1=0; k1<sh1.data.Count; k1++)
        {
            float sh1Dot = dx*sh1.data.Points[k1].X + dy*sh1.data.Points[k1].Y;
            maxSh1 = std::max(maxSh1, sh1Dot);
            minSh1 = std::min(minSh1, sh1Dot);
        }

        float maxSh2 =-INFINITY;
        float minSh2 = INFINITY;
        for(int k2=0; k2<sh1.data.Count; k2++)
        {
            float sh2Dot = dx*sh2.data.Points[k2].X + dy*sh2.data.Points[k2].Y;
            maxSh2 = std::max(maxSh2, sh2Dot);
            minSh2 = std::min(minSh2, sh2Dot);
        }

        if(!(maxSh1 >= minSh2 && maxSh2 >= minSh1))
            return false;
    }

    return true;
}

int main()
{
    srand(time(NULL));

    XEvent event;
    KeySym key;
    char text[255];

    X11WindowManager* X11panel = new X11WindowManager(true);
    
    Shape* Polygon = new Shape(RANDOM, vec2(250.0f, 250.0f), 50.0f); 
    Shape* Polygon0 = new Shape(PENTAGON, vec2(200.0f, 400.0f), 50.0f);
    vec2 a = vec2(1,1);
    int last;
    X11panel -> DrawPolygon(*Polygon, "gray0");

    while(true)
    {
       XNextEvent(X11panel->Dis(), &event);

       if(event.type == ButtonPress)
       {
           X11panel -> DrawPolygon(*Polygon, "gray0");
  

           std::cout << event.xbutton.x << "  " << event.xbutton.y << '\n';
       }
       else if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key,  0) == 1)
       {
            XClearWindow(X11panel->Dis(), X11panel->Win());

            switch(text[0])
            {
                case 'w': last = Transform(*Polygon, a, 1, 20.0f); break;
                case 's': last = Transform(*Polygon, a,-1, 20.0f); break;
                case 'q': a = Rot(*Polygon, rotmat2x2(pi/30)); break;
                case 'e': a = Rot(*Polygon, rotmat2x2(pi/-30)); break;
                default: break;
            }

            if(checkCollision(*Polygon, *Polygon0) && checkCollision(*Polygon0, *Polygon))
                Transform(*Polygon0, a,last, 20.0f);
            
            
            X11panel -> DrawPolygon(*Polygon, "gray0");
            X11panel -> DrawPolygon(*Polygon0, "gray0");
            
       }
    }

    return 0;
}