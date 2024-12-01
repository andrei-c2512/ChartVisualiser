#include "MainLayout.h"

void initMainLayout(MainLayout* layout , Size size0){
    int m = 5;
    layout->margin = { m , m , m, m};

    layout->x = layout->margin.left;
    layout->y = layout->margin.top;

    layout->s = adjustSizeToMargins(size0 , layout->margin);
    logSize(layout->s);
    //logSize(layout->s);
    layout->functionView = new FunctionView;
    layout->chartView = new ChartView;

    layout->redraw = true;

    //if you want to change the aspect ratio
    layout->chartStretch = 3;
    layout->functionViewStretch = 1;

    const int totalSegments = layout->chartStretch + layout->functionViewStretch;
    const Size chartSize = horizontalSizeByStretchFactor(layout->s , totalSegments , layout->chartStretch);
    const Size functionViewSize = horizontalSizeByStretchFactor(layout->s , totalSegments , layout->functionViewStretch);

    //TO DO : initFunctionView
    initChartView(layout->chartView , layout->x + functionViewSize.width , layout->y  , chartSize);
}

void runMainLayout(MainLayout* layout){
    runChartView(layout->chartView);
    //TO DO: run functionView


    if(layout->redraw)
    {
        drawMainLayout(layout);
        layout->redraw = false;
    }
}

void drawMainLayout(MainLayout* layout){
    setfillstyle(SOLID_FILL , BACKGROUND_MAIN);
    bar(layout->x ,
        layout->y ,
        layout->x + layout->s.width ,
        layout->y + layout->s.height);

    drawChartView(layout->chartView);
}

void destroyMainLayout(MainLayout* layout){
    destroyChartView(layout->chartView);
    delete layout->chartView;

    //TO DO: CALL DESTROY ON functionView
    delete layout->functionView;
}
