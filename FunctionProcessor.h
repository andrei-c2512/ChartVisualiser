#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED


enum StatusCode{
    OK,
    INCORECCT_PARANTHESES,
    UNKOWN
};
bool isOperation(char* s);
char* extractFunctionFromFile();
void calculate(char* s,float x);
void extractTokens(char* s);
void negativeNumbers(char* s);

#endif // FUNCTIONPROCESSOR_H_INCLUDED
