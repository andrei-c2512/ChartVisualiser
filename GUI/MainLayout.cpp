#include "MainLayout.h"
#include "Palette.h"

void initMainLayout(MainLayout* layout , Size size0 , const Mouse* mouse ){
    layout->mouse = mouse;
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
    layout->chartStretch = 2;
    layout->functionViewStretch = 1;


    const int totalSegments = layout->chartStretch + layout->functionViewStretch;
    const Size chartSize = horizontalSizeByStretchFactor(layout->s , totalSegments , layout->chartStretch);
    const Size functionViewSize = horizontalSizeByStretchFactor(layout->s , totalSegments , layout->functionViewStretch);

    initFunctionView(layout->functionView, 
        sf::Vector2i(layout->x, layout->y), 
        sf::Vector2i(functionViewSize.width, functionViewSize.height));

    initChartView(layout->chartView , layout->x + functionViewSize.width , layout->y  , chartSize , mouse);
}

void runMainLayout(MainLayout* layout, const Mouse& mouse , const Keyboard& kb){
    bool updateChart = false;
    //this looks retarded but egh , too lazy to encapsulate. It ain't that big of a project
    StackedView* stackedView = layout->functionView->stackedView;

    if (stackedView->option == Options::FunctionList) {
        updateChart = chartNeedsUpdate(&stackedView->functionPage);
    }
    
    if (updateChart) {
        auto vec = getFunctionList(&stackedView->functionPage);
        setFuncList(layout->chartView->chart, vec);
    }
    runFunctionView(layout->functionView, mouse, kb);
    runChartView(layout->chartView , mouse , kb);
}

void drawMainLayout(sf::RenderWindow& window, MainLayout* layout){
    if (layout->redraw)
    {
        sf::RectangleShape rect;
        
        rect.setFillColor(Palette::mainBackgroundColor());
        rect.setPosition(layout->x, layout->y);
        rect.setSize(sf::Vector2f(layout->s.width, layout->s.height));

        window.draw(std::move(rect));

        drawFunctionView(window, layout->functionView);
        drawChartView(window, layout->chartView);

        //layout->redraw = false;
    }
}

void destroyMainLayout(MainLayout* layout){
    destroyChartView(layout->chartView);
    delete layout->chartView;

    //TO DO: CALL DESTROY ON functionView
    delete layout->functionView;
}
