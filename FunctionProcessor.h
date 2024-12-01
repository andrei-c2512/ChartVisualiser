#ifndef FUNCTIONPROCESSOR_H_INCLUDED
#define FUNCTIONPROCESSOR_H_INCLUDED

const char BinaryOperations[] = "+*/^<>=#";
const char UnaryOperations[] = "scarel";

char* Expression();
void TokenSeparation(char* s); // I split the expression in two stacks. One for operands and one for operators


#endif // FUNCTIONPROCESSOR_H_INCLUDED
