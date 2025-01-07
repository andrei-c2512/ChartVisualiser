#include "ChartBackgrounnd.h"
#include <thread>
#include "Palette.h"


void initChartBackground(ChartBackground* background , sf::Rect<int> rect){
    background->rect = rect;

    background->offsetX = 0;
    background->offsetY = 0;

    background->zoom = 1.0f;

    background->rectSizeBase = {int(CHART_UNIT_SIZE) , int(CHART_UNIT_SIZE)};
    background->rectSizeCurrent = background->rectSizeBase;

}

void setChartBackgroundRect(ChartBackground* background, sf::Rect<int> rect) {
    background->rect = rect;
}
void drawChartBackground(sf::RenderWindow& window, ChartBackground* background){
    double startX = background->rect.left;
    double startY = background->rect.top;

    bool multithreading = false;
    if(multithreading){

    }
    else
    {
        sf::RectangleShape rect;
        rect.setFillColor(Palette::mainBackgroundColor());
        rect.setPosition(startX, startY);
        rect.setSize(sf::Vector2f(background->rect.width, background->rect.height));
    }


    double xLeft , xRight;
    double yTop , yBottom;


    double offsetX = *background->offsetX * background->zoom;
    double offsetY = *background->offsetY * background->zoom;

    double addX = background->rectSizeCurrent.x * multiplierByZoom(background->zoom);
    double addY = background->rectSizeCurrent.y * multiplierByZoom(background->zoom);

    if (offsetX >= 0) {
        xLeft = startX + background->rect.width / 2 - fmod(offsetX, addX);
        xRight = startX + background->rect.width / 2 + (addX - fmod(offsetX, addX));
    }
    else
    {
        xLeft = startX + background->rect.width / 2 - (addX - fmod(-offsetX, addX));
        xRight = startX + background->rect.width / 2 + fmod(-offsetX, addX);
    }


    if (offsetY <= 0) {
        yTop = startY + background->rect.height / 2.0 + (addY - fmod(offsetY, addY));
        yBottom = startY + background->rect.height / 2 - fmod(offsetY, addY);
    }
    else {
        yTop = startY + background->rect.height / 2.0 + fmod(-offsetY, addY);
        yBottom = startY + background->rect.height / 2.0 - (addY - fmod(-offsetY, addY));
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
        for(; xLeft > startX ; xLeft -= addX){
            line(xLeft, startY, xLeft, startY + background->rect.height);
        }
        for( ; xRight < background->rect.left + background->rect.width ; xRight += addX){
            line(xRight, startY, xRight, startY + background->rect.height);
        }

        //drawing the horizontal lines

        for( ; yTop > startY ; yTop -= addY){
            line(startX  , yTop , startX + background->rect.width , yTop);
        }

        for( ; yBottom < startY + background->rect.height ; yBottom += addY){
            line(startX  , yBottom , startX + background->rect.width , yBottom);
        }
    }

}
void setChartBackgroundZoom(ChartBackground* background , double zoom){
    if(!(zoom > MIN_ZOOM && zoom < MAX_ZOOM))
        return;

    background->zoom = zoom;
    background->rectSizeCurrent.x = double(background->rectSizeBase.x) * zoom;
    background->rectSizeCurrent.y = double(background->rectSizeBase.y) * zoom;
}
