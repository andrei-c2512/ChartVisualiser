#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

enum StatusCode{
    OK,
    INCORECCT_PARANTHESES,
    UNKOWN
};
bool isOperation(string s);
string extractFunctionFromFile();
float calculateFunction(string s,float x);
void extractTokens(string &s);
void negativeNumbers(string &s);
void initFuncManager(string& manager);
#endif // FUNCTIONPROCESSOR_H_INCLUDED
