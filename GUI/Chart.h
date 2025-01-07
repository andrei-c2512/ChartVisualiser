#pragma once
#ifndef CHART_H_INCLUDED
#define CHART_H_INCLUDED
#include "GUICommon.h"
#include "SFML/Graphics.hpp"
#include "../FunctionProcessor.h"
#include "Mouse.h"
#include "HighlightAnimation.h"


#define ORIGIN_X 0
#define ORIGIN_Y 0


struct ChartDrawingContext {
    double widthAfterZoom;
    double heightAfterZoom;
    double left;
    double top;

    double right;
    double bottom;

    float f_worldXLeft;
    float f_worldXRight;
    float dist;
    float increment;

    int32_t screenX;
    int32_t screenY;

    float segment;


    const int32_t axisWidth = 4;
    const int32_t pointRadius = 6;
    const int32_t workers = 4;
    const int32_t arrowLength = 15;
};


struct IntersectionPoint {
    IntersectionPoint(const sf::Color& color0, const sf::Vector2f& vec0, const Domain& domain0) 
        :color(color0) , val(vec0) , domain(&domain0)
    {}
    sf::Color color;
    sf::Vector2f val;

    //this is very dangerous , this should point to the domain of a function so watch out when you destroy it
    const Domain* domain;
};

struct Chart{
    sf::Rect<int> rect;

    sf::Vector2i unitSizeBase;
    sf::Vector2i unitSizeCurrent;

    Margins margin;
    double offsetX;
    double offsetY;
    double zoom;

    std::vector<std::vector<sf::Vector2f>> pointMatrix;

    float breakpoint = 0;
    bool breakpointSet = false;

    std::vector<IntersectionPoint> intersectionPoints;
    std::vector<sf::Vector2i> chartIntersectionsPos;

    sf::Text pointDetails;
    bool showPointDetails = false;

    ChartDrawingContext ctx;
    HighlightAnimation* animation = nullptr;
    sf::Vector2f highlightedPoint;
};

void initChart(Chart* chart , sf::Rect<int> rect);
void runChart(Chart* chart , const Mouse& mouse);
void drawChart(sf::RenderWindow& window, Chart* chart);
void destroyChart(Chart* chart);


//auxiliary , for drawing
//always call this at the begging of the drawing func
void initDrawingContext(Chart* chart);
bool drawAxis(sf::RenderWindow& window, Chart* chart, float x, sf::Color color);
void drawLine(sf::RenderWindow& window , int x0, int y0, int x1, int y1);
void drawBounds(sf::RenderWindow& window, Chart* chart);
void drawFunctions(sf::RenderWindow& window, Chart* chart);
void drawOx(sf::RenderWindow& window, Chart* chart);
void drawOy(sf::RenderWindow& window, Chart* chart);
void drawBreakPoints(sf::RenderWindow& window, Chart* chart);


//auxiliary , for logic
void setChartRect(Chart* chart, sf::Rect<int> rect);
void setFuncList(Chart* chart, const std::vector<FunctionString>& funcList);
void setChartZoom(Chart* chart, float zoom);
sf::Vector2f mouseToChartPos(const Chart& chart, sf::Vector2i pos);
sf::Vector2i chartToScreenPos(const Chart& chart, sf::Vector2f pos);
void calculateBreakpoints(Chart* chart);
void setChartPos(Chart& chart ,const sf::Vector2f& pos);
void highlightPoint(Chart& chart, const sf::Vector2f& pos);

#endif // CHART_H_INCLUDED
