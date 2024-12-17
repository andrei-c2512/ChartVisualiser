#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

bool isOperation(string s);
string extractFunctionFromFile();
double calculateFunction(string s,double x);
void extractTokens(string &s);
void negativeNumbers(string &s);
void initFuncManager(string& manager);
#endif // FUNCTIONPROCESSOR_H_INCLUDED
