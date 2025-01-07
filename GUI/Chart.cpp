#include "Chart.h"
#include <string.h>
#include <math.h>
#include "Palette.h"
#include "SFHelper.h"
#include <sstream>
#include <iomanip>
#include <thread>

void initChart(Chart* chart ,sf::Rect<int> rect){
    chart->rect = rect;
    chart->offsetX = chart->offsetY = 0;
    chart->zoom = 1.0f;

    const int8_t workers = 4;
    chart->pointMatrix.resize(workers);
    //just in case
    const int epsilon = 20;
    for (auto& list : chart->pointMatrix) {
        list.resize(chart->rect.width / workers + epsilon);
        list.shrink_to_fit();
    }

    chart->pointDetails.setFont(Palette::font());
    chart->pointDetails.setFillColor(Palette::mainTextColor());
    chart->pointDetails.setCharacterSize(20);

    setChartPos(*chart, sf::Vector2f(5, 5));
    highlightPoint(*chart, sf::Vector2f(0, 0));
}



void runChart(Chart* chart, const Mouse& mouse){
    const auto& ctx = chart->ctx;
    auto mousePos = mouse.windowPos;
    if (chart->rect.contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        chart->breakpoint = mouseToChartPos(*chart, mousePos).x;
        chart->breakpointSet = true;
        calculateBreakpoints(chart);
        chart->chartIntersectionsPos.resize(chart->intersectionPoints.size());
    }

    for (int32_t i = 0; i < chart->intersectionPoints.size(); i++) {
        const auto& pair = chart->intersectionPoints[i];
        chart->chartIntersectionsPos[i] = chartToScreenPos(*chart, sf::Vector2f(chart->breakpoint, pair.val.y));
    }

    //checking if any of them is hovered
    chart->showPointDetails = false;
    for (int32_t i = 0; i < chart->chartIntersectionsPos.size() ; i++) {
        const auto& chartPos = chart->chartIntersectionsPos[i];
        sf::Rect<int> rect(chartPos.x - ctx.pointRadius, chartPos.y - ctx.pointRadius, 2 * ctx.pointRadius, 2 * ctx.pointRadius);
        if (rect.contains(mousePos)) {
            std::stringstream ss;
            chart->showPointDetails = true;
            chart->pointDetails.setPosition(SFHelper::toVec2f(rect.getPosition()) + sf::Vector2f(3 * ctx.pointRadius , 0));
            
            ss << std::fixed << std::setprecision(2);
            ss << chart->breakpoint << " , " << chart->intersectionPoints[i].val.y;
            chart->pointDetails.setString(ss.str());
            break;
        }
    }

    chart->animation->pos = SFHelper::toVec2f(chartToScreenPos(*chart, chart->highlightedPoint));
}
void drawChart(sf::RenderWindow& window, Chart* chart){
    initDrawingContext(chart);
    drawFunctions(window, chart);
    drawOx(window, chart);
    drawOy(window, chart);
    drawBreakPoints(window, chart);
    
    if (chart->showPointDetails) {
        window.draw(chart->pointDetails);
    }
    
    drawBounds(window, chart);
    if (chart->animation)
        runAnimation(window, *chart->animation);
    
    const int radius = 3;
    if (chart->animation) {
        sf::CircleShape circle;
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setRadius(radius);
        circle.setFillColor(Palette::highlightColor());
        circle.setPosition(chart->animation->pos);
        window.draw(circle);
    }

}
void destroyChart(Chart* chart){
    if (chart->animation)
        delete chart->animation;
}
