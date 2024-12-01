#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED

struct Token{
    char s[3];
};

bool isOperation(Token s);
void extractTokens();
void extractFunctionFromFile(const char* fileName);
void calculate(float x);

#endif // FUNCTIONPROCESSOR_H_INCLUDED
