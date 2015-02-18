#include <iostream>
#include <string>
#include "Calc.h"

using namespace std;

int main() {
    Calc calc;
    string str;
    getline(cin,str);
    try {
        cout << calc.compute(str);
    }
    catch(runtime_error r) {
        cerr << "Error occured: " << r.what() << endl;
    }
    return 0;
}