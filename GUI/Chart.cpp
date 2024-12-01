#include "Chart.h"

void initChart(Chart* chart , int x0 , int y0 , Size size0){
    chart->x = x0;
    chart->y = y0;

    chart->s = size0;
    chart->offsetX = chart->offsetY = 0;
    chart->zoom = 1.0f;
    logSize(size0);
}
void runChart(Chart* chart){

}
void drawChart(Chart* chart){
    //drawing the xOy system
    /*int x = chart->s.width / 2 - chart->offsetX * chart->zoom;
    int y = chart->s.height / 2 - chart->offsetY * chart->zoom;

    const int barWidth = 2;
    if(x > 0 && x < chart->s.width){
        setfillstyle(SOLID_FILL, BLACK);
        bar(x + chart->x - barWidth / 2  , chart->y , x + chart->x + barWidth / 2 , chart->y + chart->s.height);
    }

    y +=4;
    if(y > 0 && y < chart->s.height){
        setfillstyle(SOLID_FILL, BLACK);
        bar(chart->x  , y - barWidth / 2, chart->x + chart->s.width , y + barWidth / 2);
    }*/

    int widthAfterZoom = (float)chart->s.width / chart->zoom;
    int heightAfterZoom = (float)chart->s.height / chart->zoom;

    std::cout << widthAfterZoom << std::endl;
    std::cout << chart->zoom << std::endl;

    int left  = -widthAfterZoom / 2 + chart->offsetX;
    int top = -heightAfterZoom / 2 + chart->offsetY;

    int right = widthAfterZoom / 2 + chart->offsetX;
    int bottom = heightAfterZoom / 2 + + chart->offsetY;


    const int barWidth = 4;
    //(0 , 0 is the origin so)
    if(ORIGIN_X > left && ORIGIN_X < right){
        int x = abs((float)left) / float(widthAfterZoom) * float(chart->s.width) + chart->x;
        //setfillstyle(SOLID_FILL, BLACK);
        setcolor(BLACK);
        line(x , chart->y , x, chart->y + chart->s.height);
    }

    if(ORIGIN_Y > top && ORIGIN_Y < bottom){
        int y  = abs((float)top) / float(heightAfterZoom) * float(chart->s.height) + chart->y;
        //setfillstyle(SOLID_FILL , BLACK);
        setcolor(BLACK);
        line(chart->x , y , chart->x + chart->s.width , y);
    }
}

void setChartZoom(Chart* chart , float zoom){
    chart->zoom = zoom;
}


void destroyChart(Chart* chart){

}
