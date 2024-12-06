#pragma once
#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED
#include "graphics.h"


struct DragHelper{
    int lastX = 0;
    int lastY = 0;

    int x = 0;
    int y = 0;

    bool lastEvent = false;
    bool event = false;
};

struct Mouse{
    DragHelper helper;
};

void updateMouse(Mouse& mouse);
void updateHelper(DragHelper& helper);
const DragHelper& getDragHelper();
#endif // MOUSE_H_INCLUDED
