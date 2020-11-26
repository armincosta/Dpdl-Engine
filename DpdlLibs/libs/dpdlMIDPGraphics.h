#dpdlMIDPGraphics.h V1.0      info@seesolutions.it
#
#Author: Armin Costa
#
#This library is implemented with Dpdl-Control-Script and comes with the standard Dpdl core Engine,
#It contains basic system abstraction functions and internal system variables
#
#Filename: dpdlMIDPGraphics.h
#License: GNU GPL
#
#This library provides  a basic interaction layer for accessing MIDP Graphic functiontionalities
#
function gSetCurrent(int component)
     return MIDPLIB_graphicsSetCurrent(component)
end

function gRepaint(int component)
     return MIDPLIB_graphicsRepaint(component)
end

function gClear(int component)
     return MIDPLIB_graphicsClear(component)
end

function gSetColor(int component, int r, int g, int b)
     return MIDPLIB_graphicsSetColor(component, r, g, b)
end

function gDrawLine(int component, int x1, int y1, int x2, int y2)
     return MIDPLIB_graphicsDrawLine(component, x1, y1, x2, y2)
end

function gDrawRect(int component, int x, int y, int w, int h)
     return MIDPLIB_graphicsDrawRect(component, x, y, w, h)
end

function gFillRect(int component, int x, int y, int w, int h)
    return MIDPLIB_graphicsFillRect(component, x, y, w, h)
end

function gDrawString(int component, string str, int x, int y, int anchor)
     return MIDPLIB_graphicsDrawString(component, str, x, y, anchor)
end


#params && anchor points
int BASELINE = 64
int BOTTOM = 32
int DOTTED = 1
int HCENTER = 1
int LEFT = 4
int RIGHT = 8
int SOLID = 0
int TOP = 16
int VCENTER = 2

#start


