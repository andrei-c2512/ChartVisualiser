#ifndef VALIDATION_H_INCLUDED
#define VALIDATION_H_INCLUDED

enum StatusCode {
    OK,
    INVALID_CHARACTER,
    INCORRECT_PARENTHESES,
    EMPTY_PARENTHESES,
    SYNTAX_ERROR,
    MISSING_UNARY_PARENTHESIS,
    INVALID_NUMBER,
    INVALID_BINARY_OPERATION
};

StatusCode isValidParenthesis(string s);
StatusCode isNegativeNumber(string &s);
StatusCode isValidUnaryOperation(string s);
StatusCode isValidBinaryOperation(string &s);
void noSpaces(string &s);
StatusCode isValidNumber(string &s);
StatusCode validate(string &s);
#endif // VALIDATION_H_INCLUDED
