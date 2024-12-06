#include "ChartView.h"
#include "Mouse.h"

void initChartView(ChartView* view , int x0 , int y0  ,Size size0 , const Mouse* mouse){
    view->mouse = mouse;
    view->x = x0;
    view->y = y0;

    const int m = 10;
    view->margin = { m , m , m , m};
    view->s = adjustSizeToMargins(size0 , view->margin);

    view->chart = new Chart;
    view->background = new ChartBackground;

    //TO DO : init chart
    initChartBackground(view->background , x0 , y0 , size0);
    initChart(view->chart , x0 , y0 , size0);
}
void runChartView(ChartView* view){
    const float zoomIncrease = 1.05f;
    const float zoomDecrease = 0.95f;
    if(kbhit()){
        char ch = getch();
        int moveFactor = 5;
        switch(ch){
        case 'a':
            moveChartX(view , -moveFactor);
            break;
        case 'd':
            moveChartX(view , moveFactor);
            break;
        case 'w':
            moveChartY(view , -moveFactor);
            break;
        case 's':
            moveChartY(view , moveFactor);
            break;
        case '+':
            setChartBackgroundZoom(view->background , view->background->zoom * zoomIncrease);
            setChartZoom(view->chart , view->chart->zoom * zoomIncrease);
            view->redraw = true;
            break;
        case '-':
            setChartBackgroundZoom(view->background , view->background->zoom * zoomDecrease);
            setChartZoom(view->chart , view->chart->zoom * zoomDecrease);
            view->redraw = true;
            break;
        }
    }

    const DragHelper& helper = view->mouse->helper;
    if(helper.event){
        moveChartX(view, helper.lastX - helper.x);
        moveChartY(view, helper.lastY - helper.y);
    }
    //checking for mouse drag

    if(view->redraw){
        drawChartView(view);
        view->redraw = false;
    }
}
void drawChartView(ChartView* view){
    drawChartBackground(view->background);
    drawChart(view->chart);
}

//delta x
void moveChartX(ChartView* view, int dx){
    view->background->offsetX += dx;
    view->chart->offsetX += dx;

    if(dx)
    view->redraw = true;
}
//delta y
void moveChartY(ChartView* view, int dy){
    view->background->offsetY += dy;
    view->chart->offsetY += dy;

    if(dy)
    view->redraw = true;
}


void destroyChartView(ChartView* view){
    destroyChart(view->chart);
    //TO DO: destroy background

    delete view->chart;
    delete view->background;
}
