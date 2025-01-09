#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include <string>
#include <vector>
#include "MathConcepts.h"
#include "FunctionProcessor.h"

void printEquation(const Equation& v);
void printPoint(const sf::Vector2f& v);
void printInterv(const Interv& v);
vector<sf::Vector2f> calculateExtremMax(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,
	double a, double b, sf::Vector2f& maxGlobal);
vector<sf::Vector2f> calculateExtremMin(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,
	double a, double b, sf::Vector2f& minGlobal);
Equation plusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
Equation minusHorizontalAsymptote(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
Equation plusSlantAsymptote(std::string s, stack<char> operators, stack<double> operands);
Equation minusSlantAsymptote(std::string s, stack<char> operators, stack<double> operands);
bool isVerticalAsymptote(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double x);
vector<Equation> verticalAsymptotes(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps,double a, double b);
double limitPoz(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
double limitNeg(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps);
double calculateIntegral(std::string s, stack<char> operators, stack<double> operands, vector<CalculationStep> Steps,double a, double b);
vector<Interv> interval(string s, stack<char> operators, stack<double> operands, vector<CalculationStep> steps, double a, double b);
#endif// TOOLS_H_INCLUDED
