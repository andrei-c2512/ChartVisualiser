#include <bits/stdc++.h>
#include "FunctionProcessor.h"

using namespace std;

int main()
{
    char* s=new char[101];
    s=extractFunctionFromFile();
    extractTokens(s);
    calculate(s,5);

    return 0;
}
