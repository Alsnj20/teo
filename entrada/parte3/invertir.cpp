#include <iostream>
#include <string>
using namespace std;

int invertir(int n)
{
    string numStr = to_string(n);
    string invertidoStr = "";

    for (int i = numStr.size() - 1; i >= 0; i--)
    {
        invertidoStr += numStr[i];
    }

    return stoi(invertidoStr);
}
