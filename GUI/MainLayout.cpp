#include "MainLayout.h"
#include "Palette.h"
#include "SharedData.hpp"


MainLayout* initMainLayout(const sf::RenderWindow* window , sf::Rect<int> rect ){
    MainLayout* layout = new MainLayout;
    layout->window = window;
    int m = 0;
    layout->margin = { m , m , m, m};
    layout->rect = rect;
    const auto adjustedRect = adjustRectToMargins(rect, layout->margin);

    layout->functionView = new FunctionView;
    layout->chartView = new ChartView;
    layout->previewModeUI = initPreviewModeUI(adjustedRect);

    //if you want to change the aspect ratio
    layout->chartStretch = 2;
    layout->functionViewStretch = 1;
    layout->previewMode = false;

    const int totalSegments = layout->chartStretch + layout->functionViewStretch;
    const int chartSize = horizontalSizeByStretchFactor(adjustedRect.width, totalSegments , layout->chartStretch);
    const int functionViewSize = horizontalSizeByStretchFactor(adjustedRect.width, totalSegments , layout->functionViewStretch);

    initFunctionView(layout->functionView,
        sf::Rect(sf::Vector2i(layout->rect.left + layout->margin.left, layout->rect.top + layout->margin.top),
        sf::Vector2i(functionViewSize, adjustedRect.height)));

    initChartView(layout->chartView , 
        sf::Rect<int>(adjustedRect.left + functionViewSize , adjustedRect.top  , chartSize , adjustedRect.height));

    return layout;
}

void setComponentRatio(MainLayout* layout, int funcViewRatio, int chartViewRatio) {
    layout->functionViewStretch = funcViewRatio;
    layout->chartStretch = chartViewRatio;

    const int totalSegments = layout->chartStretch + layout->functionViewStretch;
    const int chartSize = horizontalSizeByStretchFactor(layout->rect.width, totalSegments, layout->chartStretch);
    const int functionViewSize = horizontalSizeByStretchFactor(layout->rect.width, totalSegments, layout->functionViewStretch);


    auto chartViewRect = layout->chartView->rect;
    chartViewRect.left = functionViewSize + layout->margin.left;
    chartViewRect.width = chartSize;
    setChartViewRect(layout->chartView, chartViewRect);
}


void setPreviewMode(MainLayout* layout ,bool state) {
    if (layout->previewMode == state) return;

    layout->previewMode = state;
    if (state) {
        setComponentRatio(layout, 0, 1);
        layout->drawPreviewUI = true;
    }
    else {
        setComponentRatio(layout, 1, 2);
        layout->drawPreviewUI = false;
    }
}
void runMainLayout(MainLayout* layout, const Mouse& mouse , const Keyboard& kb){
    //this looks retarded but egh , too lazy to encapsulate. It ain't that big of a project
    if (layout->screenshotQueued && layout->clock->getElapsedTime().asSeconds() > 0.3f) {
        saveChartToFile(layout);

        layout->screenshotQueued = false;
        layout->drawPreviewUI = true;
    }

    StackedView* stackedView = layout->functionView->stackedView;

    if (stackedView->option == Options::FunctionList) {
        if (layout->previewMode == false) {
            bool updateChart = chartNeedsUpdate(&stackedView->functionPage) ||
                (stackedView->functionPage.list.size() != SharedData::funcList.size());

            if (updateChart) {
                auto vec = getFunctionList(&stackedView->functionPage);
                setFuncList(layout->chartView->chart, vec);
            }

            if (saveToFilePressed(&stackedView->functionPage)) {
                setPreviewMode(layout, true);
            }
        }
        else {
            if (layout->previewModeUI->saveToFileButton.state == ViewState::PRESSED) {
                layout->drawPreviewUI = false;
                layout->screenshotQueued = true;
                layout->clock = new sf::Clock;
            }
            else if (layout->previewModeUI->goBackButton.state == ViewState::PRESSED) {
                setPreviewMode(layout, false);
            }
        }
    }


    if (layout->previewMode == false) {
        runFunctionView(layout->functionView, mouse, kb , *layout->chartView->chart);
    }
    else
    {
        runPreviewModeUI(layout->previewModeUI, mouse);
    }
    runChartView(layout->chartView, mouse, kb);
}

void saveChartToFile(MainLayout* layout) {
    const char* filters[] = { "*.bmp" };
    std::string path = tinyfd_saveFileDialog("Save chart", "Chart", 1, filters, "Image Files (*.bmp)");
    if (path.size()) {
        sf::Texture screenTexture;
        screenTexture.create(layout->window->getSize().x, layout->window->getSize().y);
        screenTexture.update(*layout->window);

        sf::Image img = screenTexture.copyToImage();

        int32_t pos = path.rfind('\\');

        std::string fileName = path.substr(pos + 1);
        //extracting the file name

        if (img.saveToFile((fileName + ".bmp"))) {
            std::cout << "Succes";
        }
        else
            std::cout << "Failed to save screenshot";
    }
}

void drawMainLayout(sf::RenderWindow& window, MainLayout* layout){
    if (layout->previewMode == false) {
        sf::RectangleShape rect;

        rect.setFillColor(Palette::mainBackgroundColor());
        rect.setPosition(layout->rect.left, layout->rect.top);
        rect.setSize(sf::Vector2f(layout->rect.width, layout->rect.height));

        window.draw(std::move(rect));

        drawFunctionView(window, layout->functionView);
        drawChartView(window, layout->chartView);
    }
    else {
        drawChartView(window, layout->chartView);
        if(layout->drawPreviewUI)
            drawPreviewModeUI(window, layout->previewModeUI);
    }
}

void destroyMainLayout(MainLayout* layout){
    destroyChartView(layout->chartView);
    delete layout->chartView;

    destroyFunctionView(layout->functionView);
    delete layout->functionView;

    delete layout->previewModeUI;
}

void updatePalette(MainLayout& layout) {

}