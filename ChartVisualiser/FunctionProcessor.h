#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED

//<<<<<<< HEAD
struct Token{
    char s[3];
};

bool isOperation(Token s);
void extractTokens();
void extractFunctionFromFile(const char* fileName);
void calculate(float x);
//=======
const char BinaryOperations[] = "+*/^<>=#";
const char UnaryOperations[] = "scarel";

char* Expression();
void TokenSeparation(char* s); // I split the expression in two stacks. One for operands and one for operators

//>>>>>>> 682d52f11c65fed9e12a12a5d83f7b6aba76dfa1

#endif // FUNCTIONPROCESSOR_H_INCLUDED
