#ifndef GUICOMMON_H_INCLUDED
#define GUICOMMON_H_INCLUDED
#include <iostream>


struct Size{
    int width;
    int height;
};

struct Margins{
    int left;
    int top;
    int right;
    int bottom;
};

struct Rect{
    int x , y;
    Size s;
};


bool intersection(const Rect& rect1 , const Rect& rect2);
Size adjustSizeToMargins(const Size& s , const Margins& margin);
Size horizontalSizeByStretchFactor(const Size& totalSize , int segments , int stretch);

//for logging
void logSize(Size s);
#endif // GUICOMMON_H_INCLUDED
