#include <iostream>
#include "GUI/MainLayout.h"
#include "graphics.h"
#include <conio.h>


#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 800

using namespace std;

int main()
{
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);


    MainLayout* mainLayout = new MainLayout;
    initMainLayout(mainLayout , {WINDOW_WIDTH , WINDOW_HEIGHT});

    while(!_kbhit()){
        runMainLayout(mainLayout);
    }

    closegraph();
    destroyMainLayout(mainLayout);
    delete mainLayout;

    return 0;
}
