#include<iostream>
#include<string>
#include"FunctionProcessor.h"
#include"Tools.h"
#include <iomanip>
#include <cmath>
#include <sstream>
#define infinit INT_MAX
#define epsi 0.01

using namespace std;
void printPoint(const Point& v) {
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
vector<Point> calculateExtrem(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b)
{
    vector<Point> extremPoints;
    double x = calculateViaSteps(s, operators, operands, steps, a), y = calculateViaSteps(s, operators, operands, steps, a+0.01);
    double maxGlobal = -infinit, indMax = 0, minGlobal = infinit, indMin = 0;
    for (double i = a * 100 + 2 ; i <= b * 100; i ++)
    {
        double z = calculateViaSteps(s, operators, operands, steps, i*0.01);
        if (x < y && z < y && !isnan(y) && !isnan(x) && !isnan(z))
        {
            extremPoints.push_back(Point(i*0.01- 0.01,y));
            if (y > maxGlobal)
                maxGlobal = y, indMax = i;
        }
        if (x > y && z > y && !isnan(y) && !isnan(x) && !isnan(z))
        {
            extremPoints.push_back(Point(i * 0.01 - 0.01, y));
            if (y < minGlobal)
                minGlobal = y, indMin = i;
        }
        x = y;
        y = z;
    }
    /*if     (maxGlobal != -infinit)
        cout << fixed << setprecision(2) << '\n' << indMax << ' ' << maxGlobal << " Maxim Global" << '\n';
    if (minGlobal != infinit)
        cout << fixed << setprecision(2) << '\n' << indMin << ' ' << minGlobal << " Minim Global" << '\n';
    */
    return extremPoints;
}
/*Equation horizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    Equation result;

    double positivInfinit = limitPoz(s,operators,operands,steps), negativeInfinit = limitNeg(s, operators, operands, steps);
    if (abs(positivInfinit) < infinit)
    {
        cout << "Horizontal asymptote to inf: y = " << positivInfinit << '\n';
        result.offset=positivInfinit;
    }
    if (abs(negativeInfinit) < infinit)
    {
        cout << "Horizontal asymptote to -inf: y = " << negativeInfinit << '\n';
        result.offset=negativeInfinit;
    }
    return result;
}*/
Equation slantAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps)
{
    Equation result(0,0,false);
    string t = "(" + s + "/x)";
    initFunc(t);
    double m = limitPoz(t, operators, operands, steps);
    if (abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str = ss.str();
        string p = "( " + s + "- " + str + " * x )";
        double n = limitPoz(p, operators, operands, steps);
        result = Equation(n, m, 1);
    }
    return result;
    /*m = limitNeg(t, operators, operands, steps);
    if (abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str = ss.str();
        string p = "( " + s + "- " + str + " * x )";
        double n = limitPoz(p, operators, operands, steps);
        cout << "Slant asymptote to -infinit y = ";
        if (m != 1)
            cout << m << "*";
        cout << "x";
        if (n != 0)
        {
            if (n > 0)
                cout << "+" << n;
            else
                cout << n;
        }
    }*/
}
bool isVerticalAsymptote(string s,stack<char> operators, stack<double> operands,vector<CalculationStep> steps, double x)
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
vector<Equation> verticalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b)
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

double integral(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b)
{
    double h = b - a; 
    double x1 = a + h / 3;
    double x2 = a + 2 * h / 3;

    // Aplicam formula Simpson's 3/8
    double integral = (h / 8.0) * (calculateViaSteps(s, operators, operands, steps, a) + 3 * calculateViaSteps(s, operators, operands, steps, x1) + 3 * calculateViaSteps(s, operators, operands, steps, x2) + calculateViaSteps(s, operators, operands, steps, b));
    return integral;
}

double calculateIntegral(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> Steps, double a, double b)
{
    double result = 0;
    for (double i = a; i < b; i++)
        result += integral(s, operators, operands, Steps, i, i + 1);
    return result;
}

