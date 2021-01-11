#ifndef X11WINDOWMANAGER_H
#define X11WINDOWMANAGER_H
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "Geometry.h"


class X11WindowManager
{
    public: 
        X11WindowManager(bool AutoWindowCreate);
        void InitializeWindow(const char* ForegroundColor = "gray0", const char* BackgroundColor = "gray100", int WindowPositionX = 200, int WindowPositionY = 200, unsigned int WindowWidth = 500, unsigned int WindowHeight = 500);
        void create_colorMap();
        unsigned int getColors(const char* color);
        
        virtual ~X11WindowManager();

        inline Display* Dis() { return mainDisplay; }
        inline Window Win() { return mainWindow; }
        inline int Scr() { return screen; }
        inline GC gc() { return graphicContext; }
        inline int Width() { return wWidth; }
        inline int Height() { return wHeight; }

        void DrawPolygon(Shape& shape, const char* color);

    private:    

        Display *mainDisplay;   
        int screen;
        Window mainWindow;
        GC graphicContext;
        int wWidth;
        int wHeight;

};

#endif