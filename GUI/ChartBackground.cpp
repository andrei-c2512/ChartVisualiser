#include "ChartBackgrounnd.h"
#include <thread>
#include "Palette.h"


void initChartBackground(ChartBackground* background , int x , int y , Size size0){
    background->x = x;
    background->y = y;

    background->offsetX = 0;
    background->offsetY = 0;

    background->zoom = 1.0f;
    background->s = size0;

    background->rectSizeBase = {int(CHART_UNIT_SIZE) , int(CHART_UNIT_SIZE)};
    background->rectSizeCurrent = background->rectSizeBase;

}
void drawChartBackground(sf::RenderWindow& window, ChartBackground* background){
    int startX = background->x;
    int startY = background->y;

    bool multithreading = false;
    if(multithreading){

    }
    else
    {
        sf::RectangleShape rect;
        rect.setFillColor(Palette::mainBackgroundColor());
        rect.setPosition(startX, startY);
        rect.setSize(sf::Vector2f(background->s.width, background->s.height));
    }


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
    auto line = [&window](int x, int y, int x1, int y1) {
        sf::Vertex line[2] = {
                sf::Vertex(sf::Vector2f(x , y) , Palette::backgroundLineColor()) ,
                sf::Vertex(sf::Vector2f(x1 , y1), Palette::backgroundLineColor())
        };
        window.draw(line, 2, sf::Lines);
        };

    if(multithreading){

    }
    else
    {
        for(; xLeft > startX ; xLeft -= background->rectSizeCurrent.width){
            line(xLeft, startY, xLeft, startY + background->s.height);
        }
        for( ; xRight < background->x + background->s.width ; xRight += background->rectSizeCurrent.width){
            line(xRight, startY, xRight, startY + background->s.height);
        }

        //drawing the horizontal lines

        for( ; yTop > startY ; yTop -= background->rectSizeCurrent.height){
            line(startX  , yTop , startX + background->s.width , yTop);
        }

        for( ; yBottom < startY + background->s.height ; yBottom += background->rectSizeCurrent.height){
            line(startX  , yBottom , startX + background->s.width , yBottom);
        }
    }

}
void setChartBackgroundZoom(ChartBackground* background , float zoom){
    if(!(zoom > MIN_ZOOM && zoom < MAX_ZOOM))
        return;

    background->zoom = zoom;
    background->rectSizeCurrent.width = background->rectSizeBase.width * zoom;
    background->rectSizeCurrent.height = background->rectSizeBase.height * zoom;
}
