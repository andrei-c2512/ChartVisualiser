#include "Mouse.h"
#include <iostream>




void updateMouse(Mouse& mouse){
    updateHelper(mouse.helper);
}
void updateHelper(DragHelper& helper){
    if(helper.event){
        helper.event = !ismouseclick(WM_LBUTTONUP);
        clearmouseclick(WM_LBUTTONUP);
        helper.lastX = helper.x;
        helper.lastY = helper.y;

        helper.x = mousex();
        helper.y = mousey();
    }
    else{
        helper.event = ismouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONDOWN);
        if(helper.event){
            helper.lastX = mousex();
            helper.lastY = mousey();

            helper.x = mousex();
            helper.y = mousey();
        }
    }

}
