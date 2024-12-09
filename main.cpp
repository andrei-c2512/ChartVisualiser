#include <bits/stdc++.h>
#include "FunctionProcessor.h"

using namespace std;

int main()
{
    char* s=new char[101];
    s=extractFunctionFromFile();
    negativeNumbers(s);
    extractTokens(s);
    calculate(s,7);
    delete[] s;

    return 0;
}
