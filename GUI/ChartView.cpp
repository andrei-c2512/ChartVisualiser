#include "ChartView.h"
#include "Mouse.h"

void initChartView(ChartView* view , int x0 , int y0  ,Size size0 , const Mouse* mouse){
    view->mouse = mouse;
    view->x = x0;
    view->y = y0;

    const int m = 10;
    view->margin = { m , m , m , m};
    view->s = adjustSizeToMargins(size0 , view->margin);
    view->borderWidth = 5;
    view->chart = new Chart;
    view->background = new ChartBackground;

    //TO DO : init chart
    initChartBackground(view->background ,
        x0 + view->margin.left + view->borderWidth,
        y0 + view->margin.top + view->borderWidth,
        {view->s.width - view->borderWidth, 
        view->s.height - view->borderWidth });
    initChart(view->chart , 
        x0 + view->margin.left + view->borderWidth,
        y0 + view->margin.top + view->borderWidth,
        { view->s.width - view->borderWidth ,
        view->s.height - view->borderWidth });
}
void runChartView(ChartView* view){
    const float zoomIncrease = 1.05f;
    const float zoomDecrease = 0.95f;
    if(_kbhit()){
        char ch = _getch();
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
    sf::Rect<int> rect(view->x, view->y, view->s.width, view->s.height);

    if(helper.on && rect.contains(view->mouse->windowPos)){
        //std::cout << helper.lastPos.x - helper.currentPos.x << std::endl;
        //std::cout << helper.lastPos.y - helper.currentPos.y << std::endl;
        moveChartX(view, helper.lastPos.x - helper.currentPos.x);
        moveChartY(view, helper.lastPos.y - helper.currentPos.y);
    }
    //checking for mouse drag
}
void drawChartView(sf::RenderWindow& window, ChartView* view){
    //if (view->redraw) 
    {
        sf::RectangleShape rect;
        rect.setOutlineThickness(view->borderWidth);
        rect.setOutlineColor(Palette::mainContourColor());
        rect.setPosition(sf::Vector2f(
            view->x + view->margin.left,
            view->y + view->margin.top
        ));
        rect.setSize(sf::Vector2f(
            view->s.width,
            view->s.height
        ));
        window.draw(rect);
        drawChartBackground(window, view->background);
        drawChart(window, view->chart);
        view->redraw = false;
    }
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
