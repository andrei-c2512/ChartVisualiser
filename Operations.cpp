#include <limits.h>
#include <limits>
#include <cmath>
#include "Operations.h"
#define infinit INT_MAX
#define epsi 0.00000001


bool DifInf(double x)
{
    return fabs(infinit - fabs(x)) > infinit / 2.0;
}
double Logarithm(double x)
{
    if (x <= 0)
        return std::numeric_limits<double>::quiet_NaN();
    if (DifInf(x))
        return log(x);
    else
        return infinit;
}

double Exponential(double x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
}

double Multiply(double x, double y)
{
    if (fabs(x) < epsi || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x * y;
    else return infinit;
}

double Power(double y, double x)
{
    double p;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else
        return pow(x, y);
}
double Equal(double x, double y)
{
    return x == y;
}

double Different(double x, double y)
{
    return x != y;
}

double Smaller(double x, double y)
{
    return y < x;
}

double Bigger(double x, double y)
{
    return y > x;
}

double Plus(double x, double y)
{
    if (DifInf(x) && DifInf(y))  return x + y;
    else return infinit;
}

double Substract(double x, double y)
{
    if (DifInf(x) && DifInf(y))  return y - x;
    else return infinit;
}

double Divide(double x, double y)
{
    if (x == 0) return std::numeric_limits<double>::quiet_NaN();
    if (fabs(x) > epsi) return y / x;
    return infinit;
}

double Sinus(double x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

double Cosinus(double x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}

double Absolute(double x)
{
    if (DifInf(x))  return fabs(x);
    else return infinit;
}

double Radical(double x)
{
    if (x < 0)
        return std::numeric_limits<double>::quiet_NaN();
    if (DifInf(x) && (x > epsi)) return sqrt(x);
    else return infinit;
}
