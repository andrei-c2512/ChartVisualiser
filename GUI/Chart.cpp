#include "Chart.h"
#include <string.h>
#include <math.h>
#include "Palette.h"
#include "SFHelper.h"


void initChart(Chart* chart , int x0 , int y0 , Size size0){
    chart->x = x0;
    chart->y = y0;

    chart->s = size0;
    chart->offsetX = chart->offsetY = 0;
    chart->zoom = 1.0f;
    logSize(size0);

    const int8_t workers = std::thread::hardware_concurrency();
    chart->pointMatrix.resize(workers);
    //just in case
    const int epsilon = 20;
    for (auto& list : chart->pointMatrix) {
        list.resize(chart->s.width / workers + epsilon);
        list.shrink_to_fit();
    }
}
void runChart(Chart* chart){

}
void drawChart(sf::RenderWindow& window, Chart* chart){
    int widthAfterZoom = (double)chart->s.width / chart->zoom;
    int heightAfterZoom = round((double)chart->s.height / chart->zoom);
    int left  = -widthAfterZoom / 2 + chart->offsetX;
    int top = -heightAfterZoom / 2 + chart->offsetY;

    int right = widthAfterZoom / 2 + chart->offsetX;
    int bottom = heightAfterZoom / 2 + chart->offsetY;

    const int barWidth = 4;
    const int arrowLength = 15;
    //(0 , 0 is the origin so)
    auto axisLine = [&window](int x, int y, int x1, int y1) {
        sf::Vertex line[2] = {
            sf::Vertex(sf::Vector2f(x , y) , Palette::axisColor()) ,
            sf::Vertex(sf::Vector2f(x1 , y1), Palette::axisColor())
        };
        window.draw(line, 2, sf::Lines);
        };

    if(ORIGIN_X > left && ORIGIN_X < right){
        int x = abs((float)left) / float(widthAfterZoom) * float(chart->s.width) + chart->x;

        axisLine(x , chart->y , x, chart->y + chart->s.height);
        axisLine(x , chart->y , x - arrowLength / 2 , chart->y + arrowLength);
        axisLine(x , chart->y , x + arrowLength / 2 , chart->y + arrowLength);

        int add = CHART_UNIT_SIZE * chart->zoom;
        int coordinateAdd = 1;

        const double zoom = chart->zoom;
        if(zoom < 0.5f)
        {
            add *= 4;
            coordinateAdd *= 4;
        }
        else if(zoom < 0.75f){
            add *= 3;
            coordinateAdd *= 3;
        }
        else if(zoom < 1.0f)
        {
            add *=2 ;
            coordinateAdd *= 2;
        }

        int startY = -chart->offsetY - heightAfterZoom / 2;
        int startCount = int(abs(double(-chart->offsetY - heightAfterZoom / 2) * zoom))
                             %
                             int(CHART_UNIT_SIZE * zoom);

        if(startY > 0){
            startCount = CHART_UNIT_SIZE * zoom - startCount;
        }
        int begY = chart->y + chart->s.height - int(startCount);
        /*int begY = heightAfterZoom - int(chart->offsetY - chart->s.height / 2 * chart->zoom) % int(CHART_UNIT_SIZE * chart->zoom);

        begY = float(begY) / float(heightAfterZoom);
        begY = (float)begY * (float)chart->s.height;
        begY += chart->y;
        */

        int markWingWidth = 5;
        int worldY = -bottom / (CHART_UNIT_SIZE);

        const int space = 20;

        sf::Text text;
        for( ; begY >  chart->y ; begY -= add){
            if(worldY != 0)
            {
                //outtextxy(x + space / 2 , begY , intToString(worldY));
                text.setString(std::to_string(worldY));
                text.setFillColor(Palette::chartTextColor());
                text.setFont(Palette::font());
                text.setPosition(x + space / 2, begY);
                text.setCharacterSize(15);

                window.draw(text);
                axisLine(x - markWingWidth , begY , x + markWingWidth , begY);
            }
            worldY += coordinateAdd;
        }
        //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        //outtextxy(x + space, chart->y, "Y");
    }

    if(ORIGIN_Y > top && ORIGIN_Y < bottom){
        int y  = abs((float)top) / float(heightAfterZoom) * float(chart->s.height) + chart->y;
        //setfillstyle(SOLID_FILL , BLACK);
        axisLine(chart->x , y , chart->x + chart->s.width , y);
        axisLine(chart->x + chart->s.width , y , chart->x + chart->s.width - arrowLength , y + arrowLength / 2);
        axisLine(chart->x + chart->s.width , y , chart->x + chart->s.width - arrowLength , y - arrowLength / 2);

        int add = double(CHART_UNIT_SIZE) * chart->zoom;
        int coordinateAdd = 1;

        const double zoom = chart->zoom;
        if(zoom < 0.5f){
            add *= 4;
            coordinateAdd  *= 4;
        }
        else if(zoom < 0.75f){
            add *= 3;
            coordinateAdd *= 3;
        }
        else if(zoom < 1.0f){
            add *=2 ;
            coordinateAdd *= 2;
        }

        int startX = -chart->offsetX - widthAfterZoom / 2;
        int startCount = int(abs(double(-chart->offsetX - widthAfterZoom / 2) * zoom))
                             %
                             int(double(CHART_UNIT_SIZE) * zoom);

        if(startX > 0){
            startCount = double(CHART_UNIT_SIZE) * zoom - startCount;
        }
        int begX = chart->x + chart->s.width - int(startCount);
        /*int begY = heightAfterZoom - int(chart->offsetY - chart->s.height / 2 * chart->zoom) % int(CHART_UNIT_SIZE * chart->zoom);

        begY = float(begY) / float(heightAfterZoom);
        begY = (float)begY * (float)chart->s.height;
        begY += chart->y;
        */

        int markWingWidth = 5;
        int worldX = right / CHART_UNIT_SIZE;
        //setbkcolor(WHITE);

        //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        sf::Text text;
        const int space = 20;
        for( ; begX >  chart->x ; begX -= add){
            if(worldX != 0)
            {
                text.setString(std::to_string(worldX));
                text.setCharacterSize(15);
                text.setFillColor(Palette::chartTextColor());
                //text.setColor(Palette::graphTextColor());
                text.setPosition(begX, y + 5);
                text.setFont(Palette::font());

               // std::cout << begX << ' ' << y << std::endl;

                window.draw(text);
                //outtextxy(begX , y + 5, intToString(worldX));
                axisLine(begX , y - markWingWidth , begX , y + markWingWidth);
            }
            worldX--;
        }

        const int textSize = 20;

        //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        //setcolor(CYAN);
        //outtextxy(chart->x + chart->s.width - textSize , y + space, "X");
    }


    //drawing the chart itself
    float f_worldXLeft = left / CHART_UNIT_SIZE;
    float f_worldXRight = right / CHART_UNIT_SIZE;
    float dist = (f_worldXRight - f_worldXLeft);
    float increment = dist / float(chart->s.width);

    const int screenX = chart->x + chart->s.width / 2;
    const int screenY = chart->y + chart->s.height / 2;

    const int8_t workers = std::thread::hardware_concurrency();
    const float segment = dist / float(workers);
    std::vector<std::thread> threadList(workers);

    auto& pointMatrix = chart->pointMatrix;
    float unit_size = CHART_UNIT_SIZE * chart->zoom;

    for (const FunctionString& func : chart->funcList) {
        if (func.funcStr == "")
            continue;
        //I basically split the length of the chart to that of the amount of workers(threads)
        for (int8_t i = 0; i < workers; i++) {
            try {
                auto& pointList = pointMatrix[i];
          
                const float totalOffsetX = screenX - chart->offsetX * chart->zoom;
                const float totalOffsetY = screenY - chart->offsetY * chart->zoom;
                threadList[i] = std::thread([f_worldXLeft, segment, i, screenX, screenY, totalOffsetX, totalOffsetY,
                    increment, chart, &pointList , func , unit_size]() {
                        int32_t indList = 0;
                        auto funcCopy = func;
                        float f_left = (f_worldXLeft + float(i) * segment);
                        float f_worldXRight = (f_worldXLeft + float(i + 1) * segment);

                        for (float x = f_left; x < f_worldXRight; x += increment) {
                            pointList[indList] = sf::Vector2f(x * unit_size + totalOffsetX,
                                -calculateViaSteps(funcCopy.funcStr,funcCopy.operators, funcCopy.operands , funcCopy.steps , x) *
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

        sf::Vertex line[2] = {
             sf::Vertex(pointMatrix[0][0], func.color) ,
             sf::Vertex(sf::Vector2f(0 , 0), func.color)
        };

        for (int8_t i = 0; i < workers; i++) {
            for (sf::Vector2f& point : pointMatrix[i]) {
                line[1].position = std::move(point);
                window.draw(line, 2, sf::Lines);
                std::swap(line[0].position, line[1].position);
            }
        }
        const int epsilon = 20;
        for (auto& list : chart->pointMatrix) {
            list.resize(chart->s.width / workers + epsilon);
            list.shrink_to_fit();
        }
    }
    
    /*
    for ( FunctionString& str : chart->funcList) {
        float lastX = f_worldXLeft * CHART_UNIT_SIZE + screenX - chart->offsetX;
        float lastY = calculateFunction(str.funcStr, lastX , str.operators , str.operands) * CHART_UNIT_SIZE + screenY - chart->offsetY;
        sf::Vertex line[2] = {
            sf::Vertex(sf::Vector2f(lastX , lastY), sf::Color::Black) ,
             sf::Vertex(sf::Vector2f(0 , 0), sf::Color::Black)
        };

        for (float x = f_worldXLeft + increment; x < f_worldXRight; x += increment) {
            line[1].position.y = -calculateFunction(str.funcStr, x, str.operators, str.operands) * CHART_UNIT_SIZE + screenY - chart->offsetY;
            line[1].position.x = x * CHART_UNIT_SIZE + screenX - chart->offsetX;


            window.draw(line, 2, sf::Lines);


            line[0].position = line[1].position;
        }
    }
    */

}
//(x#0)*(x*cos(1/x))+(x=0)*0
//(x#0)*(x)+(x=0)*(-x)

void setFuncList(Chart* chart, const std::vector<FunctionString>& funcList) {
    std::vector<FunctionString>& list = chart->funcList;
    list.resize(funcList.size());

    for (int32_t i = 0; i < funcList.size(); i++) {
        if (funcList[i].needsUpdate) {
            list[i] = funcList[i];
            list[i].steps = getOpList(list[i].funcStr, list[i].operators, list[i].operands);
            list[i].needsUpdate = false;
        }
    }
}


void setChartZoom(Chart* chart , float zoom){
    if(!(zoom > MIN_ZOOM && zoom < MAX_ZOOM))
        return;
    chart->zoom = zoom;
}


void destroyChart(Chart* chart){

}
