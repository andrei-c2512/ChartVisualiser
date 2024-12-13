#include <string>
#include<iostream>
#include <stack>
#include "FunctionProcessor.h"
using namespace std;

string BinaryOperations = "+-*/^<>=#";
string UnaryOperations = "sin cos sqr abs exp ln";

void noSpaces(string &s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i]==' ')
            s.erase(i,1), i--;
}
bool isValidCharacter(string &s)
{
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]==',')
            s[i]='.';
        if(!isdigit(s[i]) && BinaryOperations.find(s[i])==string::npos && UnaryOperations.find(s[i])==string::npos && s[i]!='(' && s[i]!=')' && s[i]!='.')
        {
            s.erase(i,1);
            if(i>0)
                i--;
        }
    }
    if(s=="()")
    {
        cout << "Not a valid function";
        return false;
    }
    return true;
}

bool isValidParenthesis(string s)
{
    noSpaces(s);
    stack<char> p;
    for(int i=0; i<s.length(); i++)
        if(s[i]=='(')
            p.push('(');
        else if(s[i]==')')
        {
            if(!p.empty())
                p.pop();
            else
            {
                cout<< "Parentheses are missing or mismatched";
                return false;
            }
        }
    if(p.empty())
    {
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]=='(' && s[i+1] == ')')
            {
                cout << "Empty parenthesis";
                return false;
            }
        }
        return true;
    }
    else
    {
        cout<< "Parentheses are missing or mismatched";
        return false;
    }
}

bool isNegativeNumber(string &s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i]=='-')
        {
            if(!isdigit(s[i-1]) && s[i-1]!='x' && s[i-1]!='(')
            {
                s.insert(i,"(");
                i+=2;
                while(s[i]==' ')
                    i++;
                if(s[i]=='(')
                    while(s[i]!=')')
                        i++;
                else
                    while(isdigit(s[i]) || s[i]=='.' )
                        i++;
                s.insert(i,")");
            }
        }
    return true;
}
bool isValidNumber(string &s)
{
    for(int i=0; i<s.length(); i++)
    {
        if(isdigit(s[i]))
        {
            int j = i-1;
            while(s[j]==' ')
                j--;
            if((BinaryOperations.find(s[j])==string::npos && s[j]!='('))
                s.insert(j+1,"*"),i++;
            while(isdigit(s[i]))
                i++;
            if(s[i]=='.')
            {
                i++;
                while(isdigit(s[i]))
                i++;
            while(s[i]=='.')
            {
                s.erase(i,1);
                while(isdigit(s[i]))
                i++;
            }
            }
            j = i;
            while(s[j]==' ')
                j++;
            if(BinaryOperations.find(s[j])==string::npos && s[j]!=')')
                s.insert(j,"*");
        }
    }
    return true;
}

bool isValidUnaryOperation(string s)
{
    noSpaces(s);
    initFuncManager(s);
    int lastPoz = s.find(" ")+1,firstPoz=0;
    string p = s.substr(firstPoz,lastPoz);
    while(lastPoz<s.length())
    {
        if(isalpha(p[0]) && p[0]!='x')
        {
            if(UnaryOperations.find(p)==string::npos)
            {
                cout<<"Syntax error";
                return false;
            }
            else
            {
                firstPoz = firstPoz+lastPoz;
                lastPoz = s.find(" ",firstPoz)-firstPoz+1;
                string t = s.substr(firstPoz,lastPoz);
                if(t!="( ")
                {
                    cout<<"Missing parenthesis after "<<p;
                    return false;
                }
            }
        }
        firstPoz = firstPoz+lastPoz;
        lastPoz = s.find(" ",firstPoz)-firstPoz+1;
        p = s.substr(firstPoz,lastPoz);
    }
    return true;
}

bool isValidBinaryOperation(string &s)
{
    noSpaces(s);
    for(int i=0; i<s.length(); i++)
        if(BinaryOperations.find(s[i])!=string::npos)
        {
            if(s[i-1]=='(' && s[i]!='-')
                s.erase(i,1),i++;
            if(BinaryOperations.find(s[i+1])!=string::npos)
                s.erase(i+1,1);
        }
    if(s=="()")
    {
        cout << "Not a valid function";
        return false;
    }
    return true;
}
bool validate(string &s)
{
    if(!isValidCharacter(s))
        return false;
    if(!isValidParenthesis(s))
        return false;
    if(!isNegativeNumber(s))
        return false;
    if(!isValidUnaryOperation(s))
        return false;
    if(!isValidNumber(s))
        return false;
    if(!isValidBinaryOperation(s))
        return false;
    cout<<s<<'\n';
    return true;
}
