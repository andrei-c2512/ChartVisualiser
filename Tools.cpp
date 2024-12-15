#include<iostream>
#include<string>
#include"FunctionProcessor.h"
#include"Tools.h"
#include <iomanip>
#include <cmath>
#include <sstream>
#define infinit INT_MAX
#define epsi 0.001

using namespace std;
double limitPoz(string s)
{
    double x=1e5;
    double resPrev=calculateFunction(s,x),resCurrent=calculateFunction(s,x*2);
    while(abs(resCurrent-resPrev)>epsi)
    {
        x*=2;
        resPrev=resCurrent;
        resCurrent=calculateFunction(s,x*2);
    }
    return round(resCurrent);
}
double limitNeg(string s)
{
    double x=-1e5;
    double resPrev=calculateFunction(s,x),resCurrent=calculateFunction(s,x*2);
    while(abs(resCurrent-resPrev)>epsi)
    {
        x*=2;
        resPrev=resCurrent;
        resCurrent=calculateFunction(s,x*2);
    }
    return round(resCurrent);
}
void calculateExtrem(string s,double a, double b)
{
    double x=calculateFunction(s,a), y=calculateFunction(s,a+epsi);
    double maxGlobal=-infinit,indMax=0,minGlobal=infinit,indMin=0;
    for(double i=a+2*epsi; i<=b; i+=epsi)
    {
        double z=calculateFunction(s,i);
        if(x<y && z<y)
        {
            cout<<fixed<<setprecision(2)<<i<<' '<< y << " pct maxim" << '\n';
            if(y>maxGlobal)
                maxGlobal=y,indMax=i;
        }
        if(x>y && z>y)
        {
            cout<<fixed<<setprecision(2)<<i<<' ' << y << " pct minim" <<'\n';
            if(y<minGlobal)
                minGlobal=y,indMin=i;
        }
        x=y;
        y=z;
    }
    if(maxGlobal!=-infinit)
        cout <<fixed<< setprecision(2) << '\n' << indMax << ' ' << maxGlobal << " Maxim Global"<<'\n';
    if(minGlobal!=infinit)
        cout <<fixed<< setprecision(2) << '\n' << indMin << ' ' << minGlobal << " Minim Global"<<'\n';
}
std::vector<double> horizontalAsymptote(string s)
{
    std::vector<double> vec;

    double positivInfinit=limitPoz(s),negativeInfinit=limitNeg(s);
    if(abs(positivInfinit) < infinit){
        cout << "Horizontal asymptote to inf: y = "<<positivInfinit<<'\n';
        vec.push_back(positivInfinit);
    }
    if(abs(negativeInfinit) < infinit){
        cout << "Horizontal asymptote to -inf: y = "<<negativeInfinit<<'\n';
        vec.push_back(negativeInfinit);
    }
    return vec;
}
void slantAsymptote(string s)
{
    string t ="(" + s + "/x)";
    initFuncManager(t);
    double m=limitPoz(t);
    if(abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str= ss.str();
        string p = "( " + s + "- " + str + " * x )";
        double n = limitPoz(p);
        cout << "Oblique asymptote to +infinit: y = ";
        if(m!=1)
            cout<<m<<"*";
        cout<<"x";
        if(n!=0)
        {
            if(n>0)
                cout<<"+"<<n;
            else
                cout<<n;
        }
        cout<<'\n';
    }
    m=limitNeg(t);
    if(abs(m) < infinit && abs(m) > epsi)
    {
        stringstream ss;
        ss << m;
        string str= ss.str();
        string p = "( " + s + "- " + str + " * x )";
        double n = limitPoz(p);
        cout << "Slant asymptote to -infinit y = ";
        if(m!=1)
            cout<<m<<"*";
        cout<<"x";
        if(n!=0)
        {
            if(n>0)
                cout<<"+"<<n;
            else
                cout<<n;
        }
    }
}
void verticalAsymptote(string s, double x)
{

}
