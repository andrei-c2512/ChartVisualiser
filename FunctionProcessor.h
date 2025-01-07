#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED
#include <string>
#include <vector>
#include <stack>
#include <string_view>
#include "SFML/Graphics.hpp"
#include "MathConcepts.h"

using namespace std;

struct CalculationStep {
    CalculationStep(double(*binaryOp0)(double, double))
        :binaryOp(binaryOp0)
    {
    }
    CalculationStep(double (*unaryOp0)(double))
        :unaryOp(unaryOp0)
    {
        option = 1;
    }

    int8_t option = 0;


    double (*binaryOp)(double, double) = nullptr;
    double (*unaryOp)(double) = nullptr;
};

struct FunctionString {
    FunctionString() {
        asymptotes.resize((int)AsymptoteType::COUNT);
    }
    std::string unprocessedFunc = "";
    std::string funcStr = "";
    int32_t index = 0;
    sf::Color color;
    std::stack<char> operators;
    std::stack<double> operands;
    std::vector<CalculationStep> steps;
    std::vector<sf::Vector2f> minPoints;
    std::vector<sf::Vector2f> maxPoints;

    Domain domain;
    bool needsUpdate = false;

    std::vector<Equation> asymptotes;
};

bool isOperation(string s);
string extractFunctionFromFile();
double calculateFunction(const string& s, double x, stack<char>& operators, stack<double>& operands);
std::vector<CalculationStep> getOpList(const string& s, stack<char>& operators, stack<double>& operands);
void extractTokens(string& s);
void negativeNumbers(string& s);
void initFunc(string& manager);
double calculateViaSteps(const string& s, stack<char>& operators, stack<double>& operands,
    const std::vector<CalculationStep>& opList, double x);


#endif // FUNCTIONPROCESSOR_H_INCLUDED