#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include <string>
#include<vector>
using namespace std;
void calculateExtrem(string s,double a, double b);
std::vector<double> horizontalAsymptote(string s);
void slantAsymptote(string s);
double limitPoz(string s);
double limitNeg(string s);
#endif// TOOLS_H_INCLUDED
