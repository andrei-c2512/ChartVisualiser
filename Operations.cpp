#include <limits.h>
#include <cmath>
#include "Operations.h"
#define infinit INT_MAX
#define epsi 0.0001


bool DifInf(float x)
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;
};
float Logarithm(float x)
{
    if (x>epsi && DifInf(x))
        return log(x);
    else
        return infinit;
};

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
};

float Multiply(float x, float y)
{
    if (fabs(x) < epsi || fabs(y) < epsi) return 0;
        else if (DifInf(x) && DifInf(y)) return x*y;
            else return infinit;
            }

float Power(float x, float y)
{
    float p;
    if (x==0) return 0;
    else if (y==0) return 1;
    else if (x==infinit || y==infinit) return infinit;
    else
        return pow(x,y);
}
float Equal(float x, float y)
{
    return x==y;
}

float Different(float x, float y)
{
    return x!=y;
}

float Smaller(float x, float y)
{
    return x < y;
}

float Bigger(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x+y;
    else return infinit;
}

float Substract(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x-y;
    else return infinit;
}

float Divide(float x, float y)
{
    if (fabs(y)>epsi) return x/y;
    else return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
    };

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
};

float Absolute(float x)
{
    if (DifInf(x))  return fabs(x);
    else return infinit;
};

float Radical(float x)
{
    if (DifInf(x) && (x>epsi)) return sqrt(x);
    else return infinit;
};

