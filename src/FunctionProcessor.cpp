#include "FunctionProcessor.h"
#include <string>
#include <stack>
#include <fstream>
#include <cstring>
#include "Operations.h"
#include <string_view>
#include <algorithm>
#include <limits>
#include <cmath>
#include <limits.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const char BinaryOperations[] = "+-*/^<>=#";
const char UnaryOperations[] = "scrael";

int8_t priority(char c)
{

    if (strchr("()", c) != 0)
        return 1;
    if (strchr("=#><", c) != 0)
        return 2;
    if (strchr("+-", c) != 0)
        return 3;
    if (strchr("*/", c) != 0)
        return 4;
    if (c == '^')
        return 5;
    if (strchr(UnaryOperations, c) != 0)
        return 6;
    return 0;
}
void negativeNumbers(string& s)
{
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] == '-')
        {
            int j = 1;
            while (s[i - j] == ' ')
                j++;
            if (!isdigit(s[i - j]) && s[i - j] != 'x' && s[i - j] != ')')
            {
                s.insert(i, "0");
                i++;
            }
        }
}

string extractFunctionFromFile()
{
    string s;
    getline(fin, s);
    return s;
}
double number(const string_view s)
{
    int8_t i = 0;
    int8_t size = s.length();
    double nr = 0;
    while (isdigit(s[i]) && i < size)
    {
        nr = nr * 10 + (s[i++] - '0');
    }

    //removed the check for comma cuz we replace it before computing
    if (s[i] == '.')
    {
        i++;
        double p = 0.1f;
        while (isdigit(s[i]) && i < size)
        {
            nr = nr + (s[i++] - '0') * p;
            p *= 0.1f;
        }
    }
    return nr;
}
void extractTokens(string& s)
{
    string t;
    for (int i = 0; i < (int)s.length(); i++)
    {
        bool isUnaryOperation = (strchr(UnaryOperations, s[i]) != 0);

        if (isdigit(s[i]))
        {
            while ((isdigit(s[i]) || s[i] == '.') && i < s.length())
                t += s[i++];
            i--;
        }
        else
        {
            t += s[i];
            if (isUnaryOperation)
                if (s[i] == 'l')
                    t += s[++i];
                else
                    t += s[++i], t += s[++i];
        }
        t += " ";
    }
    s = t;
}

void applyOperation(stack<char>& operators, stack<double>& operands)
{
    char op = operators.top();
    operators.pop();
    bool isBinaryOperation = (strchr(BinaryOperations, op) != 0);
    bool isUnaryOperation = (strchr(UnaryOperations, op) != 0);

    if (isBinaryOperation)
    {
        double a = operands.top();
        operands.pop();
        double b = operands.top();
        operands.pop();
        switch (op)
        {
        case '+':
            operands.push(Plus(a, b));
            break;
        case '*':
            operands.push(Multiply(a, b));
            break;
        case '/':
            operands.push(Divide(b, a));
            break;
        case '-':
            operands.push(Substract(b, a));
            break;
        case '^':
            operands.push(Power(b, a));
            break;
        case '>':
            operands.push(Bigger(b, a));
            break;
        case '<':
            operands.push(Smaller(b, a));
            break;
        case '=':
            operands.push(Equal(b, a));
            break;
        case '#':
            operands.push(Different(b, a));
            break;
        }
    }
    else if (isUnaryOperation)
    {
        double a = operands.top();
        operands.pop();
        switch (op)
        {
        case 's':
            operands.push(Sinus(a));
            break;
        case 'c':
            operands.push(Cosinus(a));
            break;
        case 'l':
            operands.push(Logarithm(a));
            break;
        case 'a':
            operands.push(Absolute(a));
            break;
        case 'r':
            operands.push(Radical(a));
            break;
        case 'e':
            operands.push(Exponential(a));
            break;
        }
    }
}

void applyOperation(stack<char>& operators, stack<double>& operands, const CalculationStep& step) {
    operators.pop();
    if (!step.option) {
        double a = operands.top();
        operands.pop();
        double b = operands.top();
        operands.pop();

        operands.emplace(step.binaryOp(std::move(a), std::move(b)));
    }
    else {
        double a = operands.top();
        operands.pop();
        operands.emplace(step.unaryOp(std::move(a)));
    }
}
void collectOperation(stack<char>& operators, stack<double>& operands, std::vector<CalculationStep>& steps)
{
    char op = operators.top();
    operators.pop();
    bool isBinaryOperation = (strchr(BinaryOperations, op) != 0);
    bool isUnaryOperation = (strchr(UnaryOperations, op) != 0);

    if (isBinaryOperation)
    {
        double a = operands.top();
        operands.pop();
        double b = operands.top();
        operands.pop();
        switch (op)
        {
        case '+':
            operands.push(Plus(a, b));
            steps.emplace_back(&Plus);
            break;
        case '*':
            operands.push(Multiply(a, b));
            steps.emplace_back(&Multiply);
            break;
        case '/':
            operands.push(Divide(b, a));
            steps.emplace_back(&Divide);
            break;
        case '-':
            operands.push(Substract(b, a));
            steps.emplace_back(&Substract);
            break;
        case '^':
            operands.push(Power(b, a));
            steps.emplace_back(&Power);
            break;
        case '>':
            operands.push(Bigger(b, a));
            steps.emplace_back(&Bigger);
            break;
        case '<':
            operands.push(Smaller(b, a));
            steps.emplace_back(&Smaller);
            break;
        case '=':
            operands.push(Equal(b, a));
            steps.emplace_back(&Equal);
            break;
        case '#':
            operands.push(Different(b, a));
            steps.emplace_back(&Different);
            break;
        }
    }
    else if (isUnaryOperation)
    {
        double a = operands.top();
        operands.pop();
        switch (op)
        {
        case 's':
            operands.push(Sinus(a));
            steps.emplace_back(&Sinus);
            break;
        case 'c':
            operands.push(Cosinus(a));
            steps.emplace_back(&Cosinus);
            break;
        case 'l':
            operands.push(Logarithm(a));
            steps.emplace_back(&Logarithm);
            break;
        case 'a':
            operands.push(Absolute(a));
            steps.emplace_back(&Absolute);
            break;
        case 'r':
            operands.push(Radical(a));
            steps.emplace_back(&Radical);
            break;
        case 'e':
            operands.push(Exponential(a));
            steps.emplace_back(&Exponential);
            break;
        }
    }
}
double calculateFunction(const string& s, double x, stack<char>& operators, stack<double>& operands)
{
    int lastPoz = s.find(" ") + 1, firstPoz = 0;
    string p = s.substr(firstPoz, lastPoz);
    while (lastPoz < s.length())
    {
        bool isX = (p[0] == 'x');
        bool isBinaryOperation = (strchr(BinaryOperations, p[0]) != 0);
        bool isUnaryOperation = (strchr(UnaryOperations, p[0]) != 0);

        if (p[0] == '(')
            operators.push('(');
        if (p[0] == ')')
        {
            while (operators.top() != '(')
            {
                applyOperation(operators, operands);
                if (isnan(operands.top()))
                    return numeric_limits<double>::quiet_NaN();
            }
            operators.pop();
        }
        if (isX)
            operands.push(x);
        if (isdigit(p[0]))
            operands.push(number(p));
        if (isBinaryOperation || isUnaryOperation)
        {
            while (priority(operators.top()) >= priority(p[0]))
            {
                applyOperation(operators, operands);
                if (isnan(operands.top()))
                    return numeric_limits<double>::quiet_NaN();
            }
            if (p[0] == 's')
            {
                if (p[1] == 'q')
                    operators.push('r');
                else
                    operators.push(p[0]);
            }
            else
                operators.push(p[0]);
        }
        firstPoz = firstPoz + lastPoz;
        lastPoz = s.find(" ", firstPoz) - firstPoz + 1;
        p = s.substr(firstPoz, lastPoz);
    }
    while (!operators.empty()) {
        applyOperation(operators, operands);
        if (isnan(operands.top()))
            return numeric_limits<double>::quiet_NaN();
    }
    return operands.top();
}


std::vector<CalculationStep> getOpList(const string& s, stack<char>& operators, stack<double>& operands) {
    std::vector<CalculationStep> opList;

    double x = 10.0f;
    int lastPoz = s.find(" ") + 1, firstPoz = 0;
    string p = s.substr(firstPoz, lastPoz);
    while (lastPoz < s.length())
    {
        bool isX = (p[0] == 'x');
        bool isBinaryOperation = (strchr(BinaryOperations, p[0]) != 0);
        bool isUnaryOperation = (strchr(UnaryOperations, p[0]) != 0);

        if (p[0] == '(')
            operators.emplace('(');
        if (p[0] == ')')
        {
            while (operators.top() != '(')
                collectOperation(operators, operands, opList);
            operators.pop();
        }
        if (isX)
            operands.emplace(x);
        if (isdigit(p[0]))
            operands.emplace(number(p));
        if (isBinaryOperation || isUnaryOperation)
        {
            while (priority(operators.top()) >= priority(p[0]))
                collectOperation(operators, operands, opList);
            if (p[0] == 's')
            {
                if (p[1] == 'q')
                    operators.emplace('r');
                else
                    operators.emplace(p[0]);
            }
            else
                operators.emplace(p[0]);
        }
        firstPoz = firstPoz + lastPoz;
        lastPoz = s.find(" ", firstPoz) - firstPoz + 1;
        p = s.substr(firstPoz, lastPoz);
    }
    while (!operators.empty())
        collectOperation(operators, operands, opList);


    return opList;
}

double calculateViaSteps(const string& s, stack<char>& operators, stack<double>& operands,
    const std::vector<CalculationStep>& opList, double x) {
    int16_t step = 0;

    int lastPoz = s.find(" ") + 1, firstPoz = 0;

    //chestia asta cu string_view a crescut performanta cu MULT wtf
    string_view view = s;
    string_view p(s.data() + firstPoz, lastPoz);

    while (lastPoz < s.length())
    {
        int8_t opPriority = priority(p[0]);

        //foloseste else if nu if. Daca de ex p[0] e '(' , atunci de ce sa mai verific daca e si ')'?
        if (p[0] == '(')
            operators.emplace('(');
        else if (p[0] == ')')
        {
            while (operators.top() != '(') {
                applyOperation(operators, operands, opList[step++]);
                if (isnan(operands.top()))
                {
                    while (operands.empty() == false)
                        operands.pop();
                    while (operators.empty() == false)
                        operators.pop();
                    return numeric_limits<double>::quiet_NaN();
                }
            }
            operators.pop();
        }
        else if (p[0] == 'x')
            operands.emplace(x);
        else if (isdigit(p[0]))
            operands.emplace(number(p));
        else if (opPriority)
        {
            while (priority(operators.top()) >= opPriority) {
                applyOperation(operators, operands, opList[step++]);
                if (isnan(operands.top()))
                {
                    while (operands.empty() == false)
                        operands.pop();
                    while (operators.empty() == false)
                        operators.pop();
                    return numeric_limits<double>::quiet_NaN();
                }
            }
            if (p[0] == 's')
            {
                if (p[1] == 'q')
                    operators.emplace('r');
                else
                    operators.emplace(p[0]);
            }
            else
                operators.emplace(p[0]);
        }
        firstPoz = firstPoz + lastPoz;
        lastPoz = s.find(" ", firstPoz) - firstPoz + 1;

        p = view.substr(firstPoz, lastPoz);
    }
    while (!operators.empty())
    {
        applyOperation(operators, operands, opList[step++]);
        if (isnan(operands.top()))
        {
            while (operands.empty() == false)
                operands.pop();
            while (operators.empty() == false)
                operators.pop();
            return numeric_limits<double>::quiet_NaN();
        }
    }

    double result = operands.top();
    operands.pop();
    return result;
}


void initFunc(string& manager) {
    manager = "(" + manager + ")";
    negativeNumbers(manager);
    extractTokens(manager);
}
