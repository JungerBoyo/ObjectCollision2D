#include "../headers/X11WindowManager.h"

X11WindowManager::X11WindowManager(bool _AutoWindowCreate)
{
    if(_AutoWindowCreate)
        InitializeWindow();
}


void X11WindowManager::InitializeWindow(const char* _ForegroundColor, const char* _BackgroundColor, int _WindowPositionX
                                    , int _WindowPositionY, unsigned int _WindowWidth, unsigned int _WindowHeight)
{
    //unsigned int F_Color = getColors(_ForegroundColor);
    //unsigned int B_Color = getColors(_BackgroundColor);
    wWidth = _WindowWidth;
    wHeight = _WindowHeight;


    mainDisplay = XOpenDisplay((char*)0);
    screen = DefaultScreen(mainDisplay);

    unsigned int F_Color = BlackPixel(mainDisplay, screen);
    unsigned int B_Color = WhitePixel(mainDisplay, screen);

    mainWindow = XCreateSimpleWindow(mainDisplay, DefaultRootWindow(mainDisplay), _WindowPositionX, _WindowPositionY,
                                      _WindowWidth, _WindowHeight, 5, F_Color, B_Color);

    XSetStandardProperties(mainDisplay, mainWindow, "2D engine", "2D engine", None, NULL, 0, NULL);
    XSelectInput(mainDisplay, mainWindow, ExposureMask|ButtonPressMask|KeyPressMask);

    graphicContext = XCreateGC(mainDisplay, mainWindow, 0, 0);

    XSetBackground(mainDisplay, graphicContext, B_Color);
    XSetForeground(mainDisplay, graphicContext, F_Color);

    XClearWindow(mainDisplay, mainWindow);
    XMapWindow(mainDisplay, mainWindow);
}

unsigned int X11WindowManager::getColors(const char* _color)
{
    XColor tmp;

    XParseColor(mainDisplay, DefaultColormap(mainDisplay, screen), _color, &tmp);
    XAllocColor(mainDisplay, DefaultColormap(mainDisplay, screen), &tmp);

    return tmp.pixel;
}

void X11WindowManager::create_colorMap()
{}

X11WindowManager::~X11WindowManager()
{
    XFreeGC(mainDisplay, graphicContext);
    XDestroyWindow(mainDisplay, mainWindow);
    XCloseDisplay(mainDisplay);
}

void X11WindowManager::DrawPolygon(Shape& _shape, const char* _color)
{
    XSetForeground(mainDisplay, graphicContext, getColors(_color));

    for(int i=0; i<_shape.data.Points.size(); i++)
    {
        XDrawLine(mainDisplay, mainWindow, graphicContext,
                 _shape.data.Points[i].X, _shape.data.Points[i].Y,
                 _shape.data.Points[(i+1)%_shape.data.Points.size()].X, _shape.data.Points[(i+1)%_shape.data.Points.size()].Y);
    }

    XDrawLine(mainDisplay, mainWindow, graphicContext,
         _shape.data.center.X, _shape.data.center.Y,
         _shape.data.Points[0].X, _shape.data.Points[0].Y);

}