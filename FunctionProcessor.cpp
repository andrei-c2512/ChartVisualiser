#include "FunctionProcessor.h"
#include <bits/stdc++.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

char* Expression()
{
    char* s;
    fin.getline(s,100);
    return s;
}
void TokenSeparation(char* s)
{
    int n=strlen(s);
    stack<char> operands, operators;
    for(int i=0; i<n; i++)
    {
        if(isdigit(s[i]) || s[i]=='x')
            operands.push(s[i]);
        if(strchr(BinaryOperations,s[i])!=0)
            operators.push(s[i]);
        if(strchr(UnaryOperations,s[i])!=0)
            operators.push(s[i]), i+=2;
    }
    while (!operators.empty())
    {
        fout << operators.top() <<" ";
        operators.pop();
    }
    fout<<'\n';
    while (!operands.empty())
    {
        fout << operands.top() <<" ";
        operands.pop();
    }
}
