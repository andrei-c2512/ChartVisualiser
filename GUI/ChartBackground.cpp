#include "ChartBackgrounnd.h"


void initChartBackground(ChartBackground* background , int x , int y , Size size0){
    background->x = x;
    background->y = y;

    background->offsetX = 0;
    background->offsetY = 0;

    background->zoom = 1.0f;
    background->s = size0;

    background->rectSizeBase = {40 , 40};
    background->rectSizeCurrent = background->rectSizeBase;

}
void drawChartBackground(ChartBackground* background){
    int startX = background->x;
    int startY = background->y;

    setfillstyle(SOLID_FILL , BACKGROUND_CHART);
    bar(startX , startY , startX + background->s.width , startY + background->s.height);
    int xLeft , xRight;
    int yTop , yBottom;


    int offsetX = float(background->offsetX) * background->zoom;
    int offsetY = float(background->offsetY) * background->zoom;

    if(offsetX >= 0){
        xLeft = startX + background->s.width / 2 - (offsetX) % background->rectSizeCurrent.width;
        xRight = startX + background->s.width / 2 + (background->rectSizeCurrent.width - (offsetX) % background->rectSizeCurrent.width);
    }
    else
    {
        xLeft = startX + background->s.width / 2 - (background->rectSizeCurrent.width - (-offsetX) % background->rectSizeCurrent.width);
        xRight = startX + background->s.width / 2 + (-offsetX) % background->rectSizeCurrent.width;
    }


    if(offsetY <= 0){
        yTop = startY + background->s.height / 2 + (background->rectSizeCurrent.height - (offsetY) % background->rectSizeCurrent.height);
        yBottom = startY + background->s.height / 2 -(offsetY) % background->rectSizeCurrent.height;
    }
    else{
        yTop = startY + background->s.height / 2 + (-offsetY) % background->rectSizeCurrent.height;
        yBottom = startY + background->s.height / 2 - (background->rectSizeCurrent.height - (-offsetY) % background->rectSizeCurrent.height);
    }
    /*setcolor(BLACK);
    for( ; x < background->x + background->s.width ; x += background->rectSizeCurrent.width){
        line(x ,startY, x , startY + background->s.height);
    }*/

    //drawing the  vertical lines
    setcolor(LIGHTGRAY);
    for(; xLeft > startX ; xLeft -= background->rectSizeCurrent.width){
        line(xLeft ,startY, xLeft , startY + background->s.height);
    }
    for( ; xRight < background->x + background->s.width ; xRight += background->rectSizeCurrent.width){
        line(xRight ,startY, xRight , startY + background->s.height);
    }

    //drawing the horizontal lines

    for( ; yTop > startY ; yTop -= background->rectSizeCurrent.height){
        line(startX  , yTop , startX + background->s.width , yTop);
    }

    for( ; yBottom < startY + background->s.height ; yBottom += background->rectSizeCurrent.height){
        line(startX  , yBottom , startX + background->s.width , yBottom);
    }
}
void setChartBackgroundZoom(ChartBackground* background , float zoom){
    background->zoom = zoom;
    background->rectSizeCurrent.width = background->rectSizeBase.width * zoom;
    background->rectSizeCurrent.height = background->rectSizeBase.height * zoom;
}
