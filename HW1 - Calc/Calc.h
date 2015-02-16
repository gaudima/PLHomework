#ifndef   __CALC_H__
#define  __CALC_H__

#include <sstream>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Calc {
public:
    int compute(string strToCompute);

private:
    bool isNumber(string strToCheck);

    int isOperator(string strToCheck);

    string stackTopWithCheck();

    void stackPopWithCheck();

    bool performStackComputation(string oper);

    stringstream tokenStream;
    stack<string> operatorStack;
    stack<int> computeStack;
};


#endif