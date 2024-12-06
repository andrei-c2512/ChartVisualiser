#include "Chart.h"
#include <string.h>
#include <math.h>


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

    int widthAfterZoom = (double)chart->s.width / chart->zoom;
    int heightAfterZoom = round((double)chart->s.height / chart->zoom);
    int left  = -widthAfterZoom / 2 + chart->offsetX;
    int top = -heightAfterZoom / 2 + chart->offsetY;

    int right = widthAfterZoom / 2 + chart->offsetX;
    int bottom = heightAfterZoom / 2 + chart->offsetY;


    const int barWidth = 4;
    const int arrowLength = 15;
    //(0 , 0 is the origin so)
    if(ORIGIN_X > left && ORIGIN_X < right){
        int x = abs((float)left) / float(widthAfterZoom) * float(chart->s.width) + chart->x;
        //setfillstyle(SOLID_FILL, BLACK);
        setcolor(BLACK);

        line(x , chart->y , x, chart->y + chart->s.height);
        line(x , chart->y , x - arrowLength / 2 , chart->y + arrowLength);
        line(x , chart->y , x + arrowLength / 2 , chart->y + arrowLength);

        int add = double(CHART_UNIT_SIZE) * chart->zoom;
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
                             int(double(CHART_UNIT_SIZE) * zoom);

        if(startY > 0){
            startCount = double(CHART_UNIT_SIZE) * zoom - startCount;
        }
        int begY = chart->y + chart->s.height - int(startCount);
        /*int begY = heightAfterZoom - int(chart->offsetY - chart->s.height / 2 * chart->zoom) % int(CHART_UNIT_SIZE * chart->zoom);

        begY = float(begY) / float(heightAfterZoom);
        begY = (float)begY * (float)chart->s.height;
        begY += chart->y;
        */

        int markWingWidth = 5;
        int worldY = -bottom / (CHART_UNIT_SIZE);
        setbkcolor(WHITE);

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        const int space = 20;

        for( ; begY >  chart->y ; begY -= add){
            setcolor(CYAN);
            if(worldY != 0)
            {
                outtextxy(x + space / 2 , begY , intToString(worldY));
                setcolor(BLACK);
                line(x - markWingWidth , begY , x + markWingWidth , begY);
            }
            worldY += coordinateAdd;
        }
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(CYAN);
        outtextxy(x + space, chart->y, "Y");
    }

    if(ORIGIN_Y > top && ORIGIN_Y < bottom){
        int y  = abs((float)top) / float(heightAfterZoom) * float(chart->s.height) + chart->y;
        //setfillstyle(SOLID_FILL , BLACK);
        setcolor(BLACK);
        line(chart->x , y , chart->x + chart->s.width , y);
        line(chart->x + chart->s.width , y , chart->x + chart->s.width - arrowLength , y + arrowLength / 2);
        line(chart->x + chart->s.width , y , chart->x + chart->s.width - arrowLength , y - arrowLength / 2);

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
        setbkcolor(WHITE);

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        const int space = 20;
        for( ; begX >  chart->x ; begX -= add){
            setcolor(CYAN);
            if(worldX != 0)
            {
                outtextxy(begX , y + 5, intToString(worldX));
                setcolor(BLACK);
                line(begX , y - markWingWidth , begX , y + markWingWidth);
            }
            worldX--;
        }

        const int textSize = 20;

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(CYAN);
        outtextxy(chart->x + chart->s.width - textSize , y + space, "X");
    }
}

void setChartZoom(Chart* chart , float zoom){
    if(!(zoom > MIN_ZOOM && zoom < MAX_ZOOM))
        return;
    chart->zoom = zoom;
}


void destroyChart(Chart* chart){

}
