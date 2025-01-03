#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include <string>
#include<vector>
struct Point
{
	double x;
	double y;
	Point(double x_val, double y_val) : x(x_val), y(y_val) {}
	
};
struct Interv
{
	double a;
	double b;
	Interv(double a_val, double b_val) : a(a_val), b(b_val) {}

};
struct Equation {
	double offset = 0;
	double slope = 0;
	bool valid = false;
	Equation(double offset_val, double slope_val, bool valid_val) : offset(offset_val), slope(slope_val), valid(valid_val) {}
};
void printEquation(const Equation& v);
void printPoint(const Point& v);
void printInterv(const Interv& v);
vector<Point> calculateExtrem(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,double a, double b);
Equation plusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
Equation minusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
Equation plusSlantAsymptote(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
Equation minusSlantAsymptote(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
bool isVerticalAsymptote(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double x);
vector<Equation> verticalAsymptote(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,double a, double b);
double limitPoz(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
double limitNeg(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
double calculateIntegral(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> Steps,double a, double b);
vector<Interv> interval(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b);
#endif// TOOLS_H_INCLUDED
