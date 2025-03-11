#include "Chart.h"
#include "SharedData.hpp"
#include "../Tools.h"
#include "SFHelper.h"
#include "Palette.h"

void setChartRect(Chart* chart, sf::Rect<int> rect) {
    chart->rect = rect;
    const int epsilon = 20;
    for (auto& list : chart->pointMatrix) {
        list.resize(chart->rect.width / chart->ctx.workers + epsilon);
        list.shrink_to_fit();
    }
}
void setFuncList(Chart* chart, const std::vector<FunctionString>& funcList) {
    std::vector<FunctionString>& list = SharedData::funcList;
    list.resize(funcList.size());

    for (int32_t i = 0; i < funcList.size(); i++) {
        if (funcList[i].needsUpdate) {
            list[i] = funcList[i];
            list[i].steps = getOpList(list[i].funcStr, list[i].operators, list[i].operands);

            //negative asymptotes
            int8_t type;
            
            type = int(AsymptoteType::MINUS_X);
            list[i].asymptotes[type] = minusHorizontalAsymptote(list[i].funcStr, {}, {}, list[i].steps);

            if (list[i].asymptotes[type].valid == false)
                list[i].asymptotes[type] = minusSlantAsymptote(list[i].unprocessedFunc, {}, {});


            type = int(AsymptoteType::PLUS_X);
            list[i].asymptotes[type] = plusHorizontalAsymptote(list[i].funcStr, {}, {}, list[i].steps);

            if (list[i].asymptotes[type].valid == false)
                list[i].asymptotes[type] = plusSlantAsymptote(list[i].funcStr, {}, {});

            //auto verticalEquations = verticalAsymptotes(
             //   list[i].funcStr, {}, {}, list[i].steps, list[i].domain.left, list[i].domain.right);
                

            sf::Vector2f p;
            list[i].maxPoints = calculateExtremMax(list[i].funcStr, {}, {},
                list[i].steps, std::max(list[i].domain.left, -100.0f), std::min(list[i].domain.right, 100.0f),  p);

            list[i].minPoints = calculateExtremMin(list[i].funcStr, {}, {},
                list[i].steps, std::max(list[i].domain.left, -100.0f), std::min(list[i].domain.right, 100.0f), p);
            //list[i].extremePoints = calculateExtrem(list[i].funcStr, {}, {}, list[i].steps, list[i].domain.left, list[i].domain.right);
            //list[i].needsUpdate = false;
            
        }
    }
    calculateBreakpoints(chart);
    chart->chartIntersectionsPos.resize(chart->intersectionPoints.size());
}

void calculateBreakpoints(Chart* chart) {
    std::vector<FunctionString>& list = SharedData::funcList;
    chart->intersectionPoints.clear();
    for (int32_t i = 0; i < list.size(); i++) {
        if (list[i].funcStr.empty() == false) {
            chart->intersectionPoints.emplace_back(IntersectionPoint(list[i].color ,
                sf::Vector2f(chart->breakpoint , 
                    calculateViaSteps(list[i].funcStr, list[i].operators, list[i].operands, list[i].steps, chart->breakpoint)),
                list[i].domain));
        }
    }
}

void setChartZoom(Chart* chart, float zoom) {
    if (!(zoom > MIN_ZOOM && zoom < MAX_ZOOM))
        return;
    chart->zoom = zoom;
}

sf::Vector2f mouseToChartPos(const Chart& chart, sf::Vector2i pos) {
    return sf::Vector2f((pos.x - chart.rect.left - chart.rect.width / 2) / (CHART_UNIT_SIZE * chart.zoom) + chart.offsetX / CHART_UNIT_SIZE,
        (pos.y - chart.rect.top - chart.rect.height / 2) / (CHART_UNIT_SIZE * chart.zoom) + chart.offsetY / CHART_UNIT_SIZE);
}

sf::Vector2i chartToScreenPos(const Chart& chart, sf::Vector2f pos) {
    pos.y = -pos.y;
    return sf::Vector2i(chart.rect.left + chart.rect.width / 2 + pos.x * CHART_UNIT_SIZE * chart.zoom - chart.offsetX * chart.zoom,
        chart.rect.top + chart.rect.height / 2 + pos.y * CHART_UNIT_SIZE * chart.zoom - chart.offsetY * chart.zoom);
}

void setChartPos(Chart& chart, const sf::Vector2f& pos) {
    chart.offsetX = pos.x * CHART_UNIT_SIZE;
    chart.offsetY = -pos.y * CHART_UNIT_SIZE;
}


void highlightPoint(Chart& chart, const sf::Vector2f& pos) {
    chart.highlightedPoint = pos;
    auto screenPos = chartToScreenPos(chart, pos);
    if (chart.animation)
        delete chart.animation;
    chart.animation = createAnimation(SFHelper::toVec2f(screenPos), 0.5f, 50, Palette::highlightColor(), 5);
}
