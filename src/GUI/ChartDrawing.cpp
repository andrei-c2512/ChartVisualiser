#include "Chart.h"
#include <thread>
#include "Palette.h"
#include "SFHelper.h"
#include <cmath>
#include "SharedData.hpp"


void initDrawingContext(Chart* chart) {
    auto& c = chart->ctx;
    c.widthAfterZoom = (double)chart->rect.width / chart->zoom;
    c.heightAfterZoom = (double)chart->rect.height / chart->zoom;
    c.left = -c.widthAfterZoom / 2.0 + chart->offsetX;
    c.top = -c.heightAfterZoom / 2.0 + chart->offsetY;

    c.right = c.widthAfterZoom / 2 + chart->offsetX;
    c.bottom = c.heightAfterZoom / 2 + chart->offsetY;

    c.f_worldXLeft = c.left / CHART_UNIT_SIZE;
    c.f_worldXRight = c.right / CHART_UNIT_SIZE;
    c.dist = (c.f_worldXRight - c.f_worldXLeft);
    c.increment = c.dist / float(chart->rect.width);

    c.screenX = chart->rect.left + chart->rect.width / 2;
    c.screenY = chart->rect.top + chart->rect.height / 2;

    c.widthAfterZoom = (double)chart->rect.width / chart->zoom;
    c.heightAfterZoom = (double)chart->rect.height / chart->zoom;

    c.segment = c.dist / float(c.workers);
}
bool drawAxis(sf::RenderWindow& window, Chart* chart, float x, sf::Color color) {
    const auto& ctx = chart->ctx;
    x = chartToScreenPos(*chart, sf::Vector2f(x, 0)).x - ctx.axisWidth / 2;
    if (x > chart->rect.left && x < chart->rect.left + chart->rect.width) {
        sf::RectangleShape shape;
        shape.setPosition(sf::Vector2f(x, chart->rect.top));
        shape.setSize(sf::Vector2f(ctx.axisWidth / 2, chart->rect.height));
        shape.setFillColor(color);

        window.draw(shape);
        return true;
    }
    return false;
}

void drawBounds(sf::RenderWindow& window, Chart* chart) {
    const auto& list = SharedData::funcList;
    for (const auto& func : list) {
        if (func.domain.valid) {
            drawAxis(window, chart, func.domain.left, func.color);
            drawAxis(window, chart, func.domain.right, func.color);
        }
    }
}

void drawLine(sf::RenderWindow& window , int x0, int y0, int x1, int y1) {
    sf::Vertex line[2] = {
    sf::Vertex(sf::Vector2f(x0 , y0) , Palette::axisColor()) ,
    sf::Vertex(sf::Vector2f(x1 , y1), Palette::axisColor())
    };
    window.draw(line, 2, sf::Lines);
}

void drawFunctions(sf::RenderWindow& window, Chart* chart) {
    const auto& ctx = chart->ctx;
    std::vector<std::thread> threadList(ctx.workers);

    auto& pointMatrix = chart->pointMatrix;
    float unit_size = CHART_UNIT_SIZE * chart->zoom;

    for (const FunctionString& func : SharedData::funcList) {
        if (func.funcStr == "")
            continue;
        //I basically split the length of the chart to that of the amount of workers(threads)
        for (int8_t i = 0; i < ctx.workers; i++) {
            try {
                auto& pointList = pointMatrix[i];

                const float totalOffsetX = ctx.screenX - chart->offsetX * chart->zoom;
                const float totalOffsetY = ctx.screenY - chart->offsetY * chart->zoom;
                threadList[i] = std::thread([ctx, i, totalOffsetX, totalOffsetY,
                    chart, &pointList, func, unit_size]() {
                        int32_t indList = 0;
                        auto funcCopy = func;
                        float f_left , f_worldXRight;
                        if (func.domain.valid) {
                            f_left = std::max(func.domain.left, (ctx.f_worldXLeft + float(i) * ctx.segment));
                            f_worldXRight = std::min(func.domain.right, (ctx.f_worldXLeft + float(i + 1) * ctx.segment));
                        }
                        else
                        {
                            f_left = ctx.f_worldXLeft + float(i) * ctx.segment;
                            f_worldXRight = (ctx.f_worldXLeft + float(i + 1) * ctx.segment);
                        }



                        for (float x = f_left; x < f_worldXRight; x += ctx.increment) {
                            pointList[indList] = sf::Vector2f(x * unit_size + totalOffsetX,
                                -calculateViaSteps(funcCopy.funcStr, funcCopy.operators, funcCopy.operands, funcCopy.steps, x) *
                                unit_size + totalOffsetY);
                            indList++;
                        }
                        pointList.resize(indList);
                    });

            }
            catch (const std::exception& e) {
                std::cout << "Thread " << i << " encountered an error: " << e.what() << '\n';
            }
            //end of thread shit
        }
        for (auto& w : threadList) {
            w.join();
        }

        for (int8_t i = 0; i < ctx.workers; i++) {
            if (pointMatrix[i].empty())
                continue;

            sf::Vertex line[2] = {
                sf::Vertex(pointMatrix[i][0], func.color) ,
                sf::Vertex(sf::Vector2f(0 , 0), func.color)
            };

            auto clipRect = sf::FloatRect(chart->rect.left, chart->rect.top, chart->rect.width, chart->rect.height);

            for (const sf::Vector2f& point : pointMatrix[i]) {
                line[1].position.x = std::clamp(point.x , clipRect.left , clipRect.left + clipRect.width);
                line[1].position.y = std::clamp(point.y, clipRect.top, clipRect.top + clipRect.height);
                window.draw(line, 2, sf::Lines);
                std::swap(line[0].position, line[1].position);
            }

        }
        const int epsilon = 20;
        for (auto& list : chart->pointMatrix) {
            list.resize(chart->rect.width / ctx.workers + epsilon);
            list.shrink_to_fit();
        }
    }
}

void drawOx(sf::RenderWindow& window, Chart* chart) {
    const auto& ctx = chart->ctx;

    if (ORIGIN_X > ctx.left && ORIGIN_X < ctx.right) {
        double x = abs((double)ctx.left) / double(ctx.widthAfterZoom) * double(chart->rect.width) + (double)chart->rect.left;

        drawLine(window , x, chart->rect.top, x, chart->rect.top + chart->rect.height);
        drawLine(window , x, chart->rect.top, x - ctx.arrowLength / 2, chart->rect.top + ctx.arrowLength);
        drawLine(window , x, chart->rect.top, x + ctx.arrowLength / 2, chart->rect.top + ctx.arrowLength);

        const double zoom = chart->zoom;
        const double coordinateAdd = multiplierByZoom(zoom);
        int precision;
        if (coordinateAdd == 1.0)
            precision = 0;
        else if (coordinateAdd > 0.1)
            precision = 1;
        else
            precision = 2;

        double add = CHART_UNIT_SIZE * chart->zoom * coordinateAdd;


        double startY = -chart->offsetY - ctx.heightAfterZoom / 2.0;
        double startCount = fmod(abs(double(double(-chart->offsetY) - double(ctx.heightAfterZoom) / 2.0) * zoom)
            , add);

        if (startY > 0) {
            startCount = add - startCount;
        }
        double begY = (double)chart->rect.top + (double)chart->rect.height - startCount;


        int markWingWidth = 5;
        double c = round(-(double(double(chart->rect.height)) / zoom / 2.0 + chart->offsetY));
        double worldY = c / (CHART_UNIT_SIZE);
        int aux = worldY / coordinateAdd;
        worldY = (double)aux * coordinateAdd;

        float worldYF = worldY;

        const int space = 20;

        sf::Text text;
        for (; begY > (double)chart->rect.top; begY -= add) {
            int x1 = abs((int)(worldYF * 100));
            int x2 = int(coordinateAdd * 200);
            if (worldYF != 0.0)
            {
                text.setString(toString(worldYF , precision));
                text.setFillColor(Palette::chartTextColor());
                text.setFont(Palette::font());
                text.setPosition(x + space / 2, begY);
                text.setCharacterSize(12);

                window.draw(text);
                drawLine(window , x - markWingWidth, begY, x + markWingWidth, begY);
            }
            worldYF += coordinateAdd;
        }
    }
}
void drawOy(sf::RenderWindow& window, Chart* chart) {
    auto axisLine = [&window](int x, int y, int x1, int y1) {
        sf::Vertex line[2] = {
            sf::Vertex(sf::Vector2f(x , y) , Palette::axisColor()) ,
            sf::Vertex(sf::Vector2f(x1 , y1), Palette::axisColor())
        };
        window.draw(line, 2, sf::Lines);
        };
    const auto& ctx = chart->ctx;
    if (ORIGIN_Y > ctx.top && ORIGIN_Y < ctx.bottom) {
        double y = abs((double)ctx.top) / double(ctx.heightAfterZoom) * double(chart->rect.height) + (double)chart->rect.top;
        axisLine(chart->rect.left, y, chart->rect.left + chart->rect.width, y);
        axisLine(chart->rect.left + chart->rect.width, y, chart->rect.left + chart->rect.width - ctx.arrowLength, y + ctx.arrowLength / 2);
        axisLine(chart->rect.left + chart->rect.width, y, chart->rect.left + chart->rect.width - ctx.arrowLength, y - ctx.arrowLength / 2);

        const double zoom = chart->zoom;
        const double coordinateAdd = multiplierByZoom(zoom);
        double add = CHART_UNIT_SIZE * chart->zoom * coordinateAdd;

        int precision;
        if (coordinateAdd == 1.0)
            precision = 0;
        else if (coordinateAdd > 0.1)
            precision = 1;
        else
            precision = 2;

        double startX = -chart->offsetX - ctx.widthAfterZoom / 2/0;
        double startCount = fmod(abs(double(-chart->offsetX - ctx.widthAfterZoom / 2.0) * zoom)
            ,add);

        if (startX > 0) {
            startCount = add - startCount;
        }

        double begX = (double)chart->rect.left + (double)chart->rect.width - startCount;

        int markWingWidth = 5;
        double worldX = ctx.right / CHART_UNIT_SIZE;
        int aux = worldX / coordinateAdd;
        double worldXF = (double)aux * coordinateAdd;

        const int space = 20;

        sf::Text text;
        for (; begX > (double)chart->rect.left; begX -= add) {
            int x1 = worldXF * 100;
            int x2 = coordinateAdd * 100;
            if (worldXF != 0 )
            {
                text.setString(toString(worldXF, precision));
                text.setCharacterSize(12);
                text.setFillColor(Palette::chartTextColor());
                text.setPosition(begX, y + 5);
                text.setFont(Palette::font());

                window.draw(text);
                axisLine(begX, y - markWingWidth, begX, y + markWingWidth);
            }
            worldXF -= coordinateAdd;
        }
    }
}

void drawBreakPoints(sf::RenderWindow& window, Chart* chart) {
    const auto& ctx = chart->ctx;

    if (chart->breakpointSet) {

        if (drawAxis(window, chart, chart->breakpoint, sf::Color::Yellow)) {
            sf::CircleShape circle;
            circle.setRadius(ctx.pointRadius);
            //circle.setOutlineThickness(1);
            for (int32_t i = 0; i < chart->chartIntersectionsPos.size(); i++) {
                const auto& intersection = chart->intersectionPoints[i];
                if (withinDomain(*intersection.domain, intersection.val.x) == false)
                    continue;

                circle.setPosition(SFHelper::toVec2f(chart->chartIntersectionsPos[i] - sf::Vector2i(ctx.pointRadius, ctx.pointRadius)));
                circle.setFillColor(chart->intersectionPoints[i].color);
                circle.setOutlineColor(sf::Color::Black);
                window.draw(circle);
            }
        }
    }
}
