#include "FunctionProcessor.h"
#include <string>
#include <stack>
#include <fstream>
#include <cstring>
#include "Operations.h"

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const char BinaryOperations[] = "+-*/^<>=#";
const char UnaryOperations[] = "scrael";
stack<char> operators;
stack<float> operands;

int priority(char c)
{
    if(strchr("()",c)!=0)
        return 0;
    if(strchr("+-",c)!=0)
        return 1;
    if(strchr("*/",c)!=0)
        return 2;
    if(c=='^')
        return 3;
    if(strchr("=#><",c)!=0)
        return 4;
    if(strchr(UnaryOperations,c)!=0)
        return 5;
    return -1 ;
}
void negativeNumbers(string &s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i]=='-')
        {
            if(!isdigit(s[i-1]) && s[i-1]!='x')
            {
                s.insert(i,"0");
                i++;
            }
        }
}

string extractFunctionFromFile()
{
    string s;
    getline(fin,s);
    s.insert(0,"(");
    s=s+")";
    return s;
}
float number(string s)
{
    int i=0;
    float nr=0;
    while(isdigit(s[i]) && i<s.length())
    {
        nr=nr*10+(s[i]-'0');
        i++;
    }
    if(s[i]=='.' || s[i]==',')
    {
        i++;
        float p=0.1;
        while(isdigit(s[i]) && i<s.length())
        {
            nr=nr+(s[i]-'0')*p;
            p*=0.1;
            i++;
        }
    }
    i--;
    return nr;
}
void extractTokens(string &s)
{
    string t;
    for(int i=0; i<s.length(); i++)
    {
        bool isUnaryOperation = (strchr(UnaryOperations,s[i]) != 0);

        if(isdigit(s[i]))
        {
            while((isdigit(s[i]) || s[i]=='.') && i<s.length())
                t += s[i++];
            i--;
        }
        else
        {
            t += s[i];
            if(isUnaryOperation)
                if(s[i]=='l')
                    t += s[++i];
                else
                    t += s[++i],t += s[++i];
        }
        t += " ";
    }
    s = t;
}
void apllyOperation()
{
    char op=operators.top();
    operators.pop();
    bool isBinaryOperation=(strchr(BinaryOperations,op)!=0);
    bool isUnaryOperation=(strchr(UnaryOperations,op)!=0);

    if(isBinaryOperation)
    {
        float a=operands.top();
        operands.pop();
        float b=operands.top();
        operands.pop();
        switch(op)
        {
        case '+':
            operands.push(Plus(a,b));
            break;
        case '*':
            operands.push(Multiply(a,b));
            break;
        case '/':
            operands.push(Divide(b,a));
            break;
        case '-':
            operands.push(Substract(b,a));
            break;
        case '^':
            operands.push(Power(b,a));
            break;
        case '>':
            operands.push(Bigger(b,a));
            break;
        case '<':
            operands.push(Smaller(b,a));
            break;
        case '=':
            operands.push(Equal(b,a));
            break;
        case '#':
            operands.push(Different(b,a));
            break;
        }
    }
    else if(isUnaryOperation)
    {
        float a=operands.top();
        operands.pop();
        switch(op)
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
float calculateFunction(string s,float x)
{
    int lastPoz = s.find(" ")+1,firstPoz=0;
    string p = s.substr(firstPoz,lastPoz);
    while(lastPoz<s.length())
    {
        bool isX = (tolower(p[0])=='x');
        bool isBinaryOperation = (strchr(BinaryOperations,p[0]) != 0);
        bool isUnaryOperation = (strchr(UnaryOperations,p[0]) != 0);

        if(p[0]=='(')
            operators.push('(');
        if(p[0]==')')
        {
            while(operators.top()!='(')
                apllyOperation();
            operators.pop();
        }
        if(isX)
            operands.push(x);
        if(isdigit(p[0]))
            operands.push(number(p));
        if(isBinaryOperation || isUnaryOperation)
        {
            while(priority(operators.top()) >= priority(p[0]))
                apllyOperation();
            if(p[0]=='s')
            {
                if(p[1]=='q')
                    operators.push('r');
                else
                    operators.push(p[0]);
            }
            else
                operators.push(p[0]);
        }
        firstPoz = firstPoz+lastPoz;
        lastPoz = s.find(" ",firstPoz)-firstPoz+1;
        p = s.substr(firstPoz,lastPoz);
    }
    while(!operators.empty())
        apllyOperation();
    return operands.top();
}

void initFuncManager(string& manager){
    negativeNumbers(manager);
    extractTokens(manager);
}
