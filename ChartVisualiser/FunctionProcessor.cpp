#include "FunctionProcessor.h"
//<<<<<<< HEAD

//=======
#include <fstream>
#include <stack>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

char* Expression()
{
    char* s = new char[101];
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
//>>>>>>> 682d52f11c65fed9e12a12a5d83f7b6aba76dfa1
