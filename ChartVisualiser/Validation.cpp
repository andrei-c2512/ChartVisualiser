#include <string>
#include<iostream>
#include <stack>
#include "FunctionProcessor.h"
#include "Validation.h"
using namespace std;

string BinaryOperations = "+-*/^<>=#";
string UnaryOperations = "sin cos sqr abs exp ln";

void noSpaces(string &s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i]==' ')
            s.erase(i,1), i--;
}
StatusCode isValidCharacter(string &s)
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
        ///cout << "Not a valid function";
        return INVALID_CHARACTER;
    }
    return OK;
}

StatusCode isValidParenthesis(string s)
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
                ///cout<< "Parentheses are missing or mismatched";
                return INCORRECT_PARENTHESES;
            }
        }
    if(p.empty())
    {
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]=='(' && s[i+1] == ')')
            {
                ///cout << "Empty parenthesis";
                return EMPTY_PARENTHESES;
            }
        }
        return OK;
    }
    else
    {
        ///cout<< "Parentheses are missing or mismatched";
        return INCORRECT_PARENTHESES;
    }
}

StatusCode isNegativeNumber(string &s)
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
    return OK;
}
StatusCode isValidNumber(string &s)
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
    return OK;
}

StatusCode isValidUnaryOperation(string s)
{
    noSpaces(s);
    initFunc(s);
    int lastPoz = s.find(" ")+1,firstPoz=0;
    string p = s.substr(firstPoz,lastPoz);
    while(lastPoz<s.length())
    {
        if(isalpha(p[0]) && p[0]!='x')
        {
            if(UnaryOperations.find(p)==string::npos)
            {
                ///cout<<"Syntax error";
                return SYNTAX_ERROR;
            }
            else
            {
                firstPoz = firstPoz+lastPoz;
                lastPoz = s.find(" ",firstPoz)-firstPoz+1;
                string t = s.substr(firstPoz,lastPoz);
                if(t!="( ")
                {
                    ///cout<<"Missing parenthesis after "<<p;
                    return MISSING_UNARY_PARENTHESIS;
                }
            }
        }
        firstPoz = firstPoz+lastPoz;
        lastPoz = s.find(" ",firstPoz)-firstPoz+1;
        p = s.substr(firstPoz,lastPoz);
    }
    return OK;
}

StatusCode isValidBinaryOperation(string &s)
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
        ///cout << "Not a valid function";
        return INVALID_BINARY_OPERATION;
    }
    return OK;
}
StatusCode validate(string &s)
{
    if(isValidCharacter(s)!=OK)
        return isValidCharacter(s);
    if(isValidParenthesis(s)!=OK)
        return isValidParenthesis(s);
    if(OK!=isNegativeNumber(s))
        return isNegativeNumber(s);
    if(OK!=isValidUnaryOperation(s))
        return isValidUnaryOperation(s);
    if(OK!=isValidNumber(s))
        return isValidNumber(s);
    if(OK!=isValidBinaryOperation(s))
        return isValidBinaryOperation(s);
    ///cout<<s<<'\n';
    return OK;
}