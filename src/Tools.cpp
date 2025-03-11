#include<iostream>
#include<string>
#include"FunctionProcessor.h"
#include"Tools.h"
#include <iomanip>
#include <cmath>
#include <sstream>
#include <stack>
#define infinit INT_MAX
#define epsi 0.01

using namespace std;
void printPoint(const sf::Vector2f& v) {
    std::cout<<fixed << setprecision(2) << v.x << ", " << v.y << std::endl;
}

void printInterv(const Interv& v) {
    std::cout << fixed << setprecision(2) << "( " << v.a << ", " << v.b << " )" << std::endl;
}
void printEquation(const Equation& v) {
    std::cout << fixed << setprecision(2) << "( " << v.offset << ", " << v.slope << " )" << std::endl;
}
double limitPoz(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    double x = 1e5;
    double resPrev = calculateViaSteps(s, operators, operands, steps, x), resCurrent = calculateViaSteps(s, operators, operands, steps, x*2);
    while (abs(resCurrent - resPrev) > epsi)
    {
        x *= 2;
        resPrev = resCurrent;
        resCurrent = calculateViaSteps(s, operators, operands, steps, x*2);
    }
    return round(resCurrent);
}
double limitNeg(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    double x = -1e5;
    double resPrev = calculateViaSteps(s, operators, operands, steps, x), resCurrent = calculateViaSteps(s, operators, operands, steps, x*2);
    while (abs(resCurrent - resPrev) > epsi)
    {
        x *= 2;
        resPrev = resCurrent;
        resCurrent = calculateViaSteps(s, operators, operands, steps, x*2);
    }
    return round(resCurrent);
}
//std::vector<sf::Vector2d>
vector<sf::Vector2f> calculateExtremMax(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,
    double a, double b, sf::Vector2f& maxGlobal)
{
    vector<sf::Vector2f> extremPoints;
    double x = calculateViaSteps(s, operators, operands, steps, a), y = calculateViaSteps(s, operators, operands, steps, a + 0.01);
    maxGlobal.y = -infinit, maxGlobal.x = 0;
    for (double i = a * 100 + 2; i <= b * 100; i++)
    {
        double z = calculateViaSteps(s, operators, operands, steps, i * 0.01);
        if (x < y && z < y && !isnan(y) && !isnan(x) && !isnan(z))
        {
            extremPoints.push_back(sf::Vector2f(i * 0.01 - 0.01, y));
            if (y > maxGlobal.y)
                maxGlobal.y = y, maxGlobal.x = i * 0.01;
        }
        x = y;
        y = z;
    }
    return extremPoints;
}
vector<sf::Vector2f> calculateExtremMin(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, 
    double a, double b, sf::Vector2f& minGlobal)
{
    vector<sf::Vector2f> extremPoints;
    double x = calculateViaSteps(s, operators, operands, steps, a), y = calculateViaSteps(s, operators, operands, steps, a + 0.01);
    minGlobal.y = infinit, minGlobal.x = 0;
    for (double i = a * 100 + 2; i <= b * 100; i++)
    {
        double z = calculateViaSteps(s, operators, operands, steps, i * 0.01);
        if (x > y && z > y && !isnan(y) && !isnan(x) && !isnan(z))
        {
            extremPoints.push_back(sf::Vector2f(i * 0.01 - 0.01, y));
            if (y < minGlobal.y)
                minGlobal.y = y, minGlobal.x = i * 0.01;
        }
        x = y;
        y = z;
    }
    return extremPoints;
}
Equation plusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    Equation result(0, 0, false);
    double limit = limitPoz(s, operators, operands, steps);
        if (abs(limit) < infinit)
        {
            result.valid = true;
        result.offset = limit;
        }
    return result;
}
Equation minusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    Equation result(0, 0, false);
    double limit = limitNeg(s, operators, operands, steps);
        if (abs(limit) < infinit)
        {
            result.valid = true;
            result.offset = limit;
        }
    return result;
}
Equation minusSlantAsymptote(string s, stack<char> operators, stack<double> operands)
{
    Equation result(0, 0, false);
    string t = "( " + s + " ) / x";
    initFunc(t);
    vector<CalculationStep> stepst = getOpList(t, operators, operands);
    double m = limitNeg(t, operators, operands, stepst);
    if (abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str = ss.str();
        string p = s + "-" + str + "*x";
        initFunc(p);
        while (!operators.empty())
            operators.pop();
        while (!operands.empty())
            operands.pop();
        vector<CalculationStep> stepsp = getOpList(p, operators, operands);
        double n = limitNeg(p, operators, operands, stepsp);
        result = Equation(n, m, 1);
    }
    return result;
}

Equation plusSlantAsymptote(string s, stack<char> operators, stack<double> operands)
{
    Equation result(0, 0, false);
    string t = "( " + s + " ) / x";
    initFunc(t);
    vector<CalculationStep> stepst = getOpList(t, operators, operands);
    double m = limitPoz(t, operators, operands, stepst);
    if (abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str = ss.str();
        string p = s + "-" + str + "*x";
        cout << s << endl << p << endl;
        initFunc(p);
        while (!operators.empty())
            operators.pop();
        while (!operands.empty())
            operands.pop();
        vector<CalculationStep> stepsp = getOpList(p, operators, operands);
        cout << p << endl;
        double n = limitPoz(p, operators, operands, stepsp);
        result = Equation(n, m, 1);
    }
    return result;
}
bool isVerticalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double x)
{
    if (abs(calculateViaSteps(s, operators, operands, steps, x - (1e-9))) >= infinit)
        return true;
    if (abs(calculateViaSteps(s, operators, operands, steps, x + (1e-9))) >= infinit)
        return true;
    return false;
}

vector<Interv> interval(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b)
{
    vector<Interv> result;
    for (double i = a * 100; i <= b * 100; i++)
    {
        double j = i;
        bool ok = 0;
        double x = calculateViaSteps(s, operators, operands, steps, j * 0.01);
            while (isnan(x) && j <= b * 100)
            {
                j++, ok = 1;
                x = calculateViaSteps(s, operators, operands, steps, j * 0.01);
            }
            if (ok == 1)
            {
                result.push_back(Interv(i * 0.01, (--j) * 0.01)), i = j;
                i = j;
            }
    }
    return result;
}
vector<Equation> verticalAsymptotes(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b)
{
    vector<Equation> vec;
    vector<Interv> in = interval(s, operators, operands, steps, a, b);
    for (const auto& v : in) {
        if (isVerticalAsymptote(s, operators, operands, steps, v.a))
            vec.push_back(Equation(0, v.a, true));
        if (isVerticalAsymptote(s, operators, operands, steps, v.b))
            vec.push_back(Equation(0, v.b, true));
    }
    return vec;
}

double integralHelper(string s, std::stack<char> operators, std::stack<double> operands, std::vector<CalculationStep> steps, double a, double b)
{
    double h = b - a; 
    double x1 = a + h / 3;
    double x2 = a + 2 * h / 3;

    // Aplicam formula Simpson's 3/8
    double result = (h / 8.0) * (calculateViaSteps(s, operators, operands, steps, a) + 3 * calculateViaSteps(s, operators, operands, steps, x1) + 3 * calculateViaSteps(s, operators, operands, steps, x2) + calculateViaSteps(s, operators, operands, steps, b));
    return result;
}

double calculateIntegral(std::string s, std::stack<char> operators, std::stack<double> operands, std::vector<CalculationStep> Steps, double a, double b)
{
    double result = 0;
    for (double i = a; i < b; i++)
        result += integralHelper(s, operators, operands, Steps, i, i + 1);
    return result;
}

