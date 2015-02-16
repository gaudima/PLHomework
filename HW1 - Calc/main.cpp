#include <iostream>
#include <string>
#include "Calc.h"

using namespace std;

int main() {
    Calc calc;
    string str;
    getline(cin,str);
    cout << calc.compute(str);
    return 0;
}