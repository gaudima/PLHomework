#ifndef   __CALC_H__
#define  __CALC_H__

#include <sstream>
#include <string>
#include <stack>
#include <iostream>
#include <stdexcept>

using namespace std;

class Calc {
public:
    //Computes given expression and returns result of computation
    //Uses simplified version of Shunting-yard algorithm
    int compute(string strToCompute); //throw(std::runtime_error)

private:
    //Checks if token is a number
    bool isNumber(string token);

    //Checks if token is an operator.
    //Returns operator priority or -1 if token is not an operator
    int isOperator(string token);

    //Returns top element of operatorStack if it is not empty
    string stackTopWithCheck();

    //Pops element from operatorStack if it is not empty
    void stackPopWithCheck();

    //Applies an operator on two top computeStack elements and pushes result back
    void performStackComputation(string oper); //throw(std::runtime_error)

    stringstream tokenStream;
    stack<string> operatorStack;
    stack<int> computeStack;
};


#endif