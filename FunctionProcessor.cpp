#include "FunctionProcessor.h"
#include <bits/stdc++.h>
#include "Operations.h"

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const char BinaryOperations[] = "+-*/^<>=#";
const char UnaryOperations[] = "scrael";
stack<char> operators;
stack<float> operands;
bool parenthesis(char* s)
{
    stack<char>p;
    p.push('(');
    for(int i=0; i<strlen(s); i++)
        if(s[i]=='(')
            p.push('(');
        else if(s[i]==')')
            p.pop();
    if(p.empty())
        return true;
    else
        return false;
}
bool isOperation(char* s)
{
    return  parenthesis(s);
}
int Priority(char c)
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
char* extractFunctionFromFile()
{
    char* s = new char[101];
    fin.getline(s,100);
    int n=strlen(s);
    strcpy(s+n,")");
    operators.push('(');
    n++;
     for(int i=0; i<n; i++)
        if(s[i]=='-')
        {
            if(i==0)
            {
                char* t = new char[101];
                strcpy(t,s+i);
                strcpy(s+i+1,t);
                s[i]='0';
                i++;
                n++;
            }
            else if(!isdigit(s[i-1]) && s[i-1]!='x')
            {
                char* t = new char[101];
                strcpy(t,s+i);
                strcpy(s+i+1,t);
                s[i]='0';
                n++;
                i++;
            }
        }
        cout<<s;
    return s;
}
float Nr(char* s)
{
    int n=strlen(s),i=0;
    float nr=0;
    while(isdigit(s[i]) && i<n)
    {
        nr=nr*10+(s[i]-'0');
        i++;
    }
    if(s[i]=='.' || s[i]==',')
    {
        i++;
        float p=0.1;
        while(isdigit(s[i]) && i<n)
        {
            nr=nr+(s[i]-'0')*p;
            p*=0.1;
            i++;
        }
    }
    i--;
    return nr;
}
void extractTokens(char* s)
{
    char t[100]="";
    int j=0;
    for(int i=0; i<strlen(s); i++)
    {
        bool isUnaryOperation = (strchr(UnaryOperations,s[i]) != 0);

        if(isdigit(s[i]))
        {
            while((isdigit(s[i]) || s[i]=='.') && i<strlen(s))
                t[j++]=s[i++];
            i--;
        }
        else
        {
            t[j++]=s[i];
            if(isUnaryOperation)
                if(s[i]=='l')
                    t[j++]=s[++i];
                else
                    t[j++]=s[++i],t[j++]=s[++i];
        }
        t[j++]=' ';
    }
    strcpy(s,t);
}
void Function()
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
void calculate(char* t,float x)
{
    char* s= new char[101];
    strcpy(s,t);
    char* p=strtok(s," ");
    while(p)
    {
        bool isX = (tolower(p[0])=='x');
        bool isBinaryOperation = (strchr(BinaryOperations,p[0]) != 0);
        bool isUnaryOperation = (strchr(UnaryOperations,p[0]) != 0);

        if(p[0]=='(')
            operators.push('(');
        if(p[0]==')')
        {
            while(operators.top()!='(')
                Function();
            operators.pop();
        }
        if(isX)
            operands.push(x);
        if(isdigit(p[0]))
            operands.push(Nr(p));
        if(isBinaryOperation || isUnaryOperation)
        {
            while(Priority(operators.top()) >= Priority(p[0]))
                Function();
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
        p=strtok(NULL," ");
    }
    while(!operators.empty())
        Function();
    fout<<operands.top();
}
