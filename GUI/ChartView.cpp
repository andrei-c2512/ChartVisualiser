#include "ChartView.h"
#include "Mouse.h"

void initChartView(ChartView* view , sf::Rect<int> rect){
    view->rect = rect;
    const int m = 10;
    view->margin = { m , m , m , m};
    const auto adjustedRect = adjustRectToMargins(rect, view->margin);
    view->borderWidth = 5;
    view->chart = new Chart;
    view->background = new ChartBackground;

    initChartBackground(view->background , adjustedRect);
    initChart(view->chart , adjustedRect);

    view->boundLeft = -100000 * CHART_UNIT_SIZE;
    view->boundRight = 100000 * CHART_UNIT_SIZE;

    view->background->offsetX = &view->chart->offsetX;
    view->background->offsetY = &view->chart->offsetY;

}

void setChartViewRect(ChartView* view, sf::Rect<int> rect) {
    view->rect = rect;
    auto adjustedRect = adjustRectToMargins(rect, view->margin);
    setChartRect(view->chart, adjustedRect);
    setChartBackgroundRect(view->background, adjustedRect);
}

void runChartView(ChartView* view , const Mouse& mouse, const Keyboard& kb){
    const double zoomIncrease = 1.05;
    const double zoomDecrease = 0.95;

    if (kb.samePoll && !kb.usedKey) {
        char ch = kb.lastKey;
        int moveFactor = 5;
        switch (ch) {
        case 'a':
            moveChartX(view, -moveFactor);
            break;
        case 'd':
            moveChartX(view, moveFactor);
            break;
        case 'w':
            moveChartY(view, -moveFactor);
            break;
        case 's':
            moveChartY(view, moveFactor);
            break;
        case '+':
            setChartBackgroundZoom(view->background, view->background->zoom * zoomIncrease);
            setChartZoom(view->chart, view->chart->zoom * zoomIncrease);
            view->redraw = true;
            break;
        case '-':
            setChartBackgroundZoom(view->background, view->background->zoom * zoomDecrease);
            setChartZoom(view->chart, view->chart->zoom * zoomDecrease);
            view->redraw = true;
            break;
        default:
            break;
        }
    }

    const DragHelper& helper = mouse.helper;

    if(helper.on && view->rect.contains(mouse.windowPos)){
        //std::cout << helper.lastPos.x - helper.currentPos.x << std::endl;
        //std::cout << helper.lastPos.y - helper.currentPos.y << std::endl;
        moveChartX(view, helper.lastPos.x - helper.currentPos.x);
        moveChartY(view, helper.lastPos.y - helper.currentPos.y);
    }
    runChart(view->chart, mouse);
}
void drawChartView(sf::RenderWindow& window, ChartView* view){
    sf::RectangleShape rect;
    rect.setOutlineThickness(view->borderWidth);
    rect.setOutlineColor(Palette::mainContourColor());
    rect.setPosition(sf::Vector2f(
        view->rect.left + view->margin.left,
        view->rect.top + view->margin.top
    ));
    rect.setSize(sf::Vector2f(
        view->rect.width - view->margin.right - view->margin.left ,
        view->rect.height - view->margin.top - view->margin.bottom
    ));
    window.draw(rect);
    drawChartBackground(window, view->background);
    drawChart(window, view->chart);
    view->redraw = false;

    if (view->previewMode) {
        drawButton(window, &view->goBackButton);
        drawButton(window, &view->saveButton);
    }
}

bool cameraInBoundsX(ChartView* view, int32_t x) {
    return x <= view->boundRight && x >= view->boundLeft;
}
bool cameraInBoundsY(ChartView* view, int32_t y) {
    return y <= view->boundBottom && y >= view->boundTop;
}

//delta x
void moveChartX(ChartView* view, int dx){
    if (cameraInBoundsX(view, view->chart->offsetX + dx))
    {
        view->chart->offsetX += double(dx) / view->chart->zoom;
        if (dx)
            view->redraw = true;
    }
}
//delta y
void moveChartY(ChartView* view, int dy){
    view->chart->offsetY += double(dy) / view->chart->zoom;

    if(dy)
    view->redraw = true;
}


void destroyChartView(ChartView* view){
    destroyChart(view->chart);
    //TO DO: destroy background

    delete view->chart;
    delete view->background;
}
