#include "Calc.h"

//Computes given expression and returns result of computation
//Uses simplified version of Shunting-yard algorithm
int Calc::compute(string strToCompute) {
    tokenStream.str(strToCompute);
    //Clear all stacks
    while (!operatorStack.empty()) {
        operatorStack.pop();
    }
    while (!computeStack.empty()) {
        computeStack.pop();
    }

    while (!tokenStream.eof()) {
        string tmpToken;
        int opPriority;
        tokenStream >> tmpToken;
        if (isNumber(tmpToken)) {
            //there is a bug in mingw32 so i cant use c++11 stoi func to convert str to int
            stringstream tmpStream(tmpToken);
            int tmpInt;
            tmpStream >> tmpInt;
            computeStack.push(tmpInt);
        }
        else if ((opPriority = isOperator(tmpToken)) != -1) {
            while (isOperator(stackTopWithCheck()) >= opPriority) {
                if (!performStackComputation(stackTopWithCheck())) {
                    return -666;
                }
                stackPopWithCheck();
            }
            operatorStack.push(tmpToken);
        }
        else if (tmpToken == "(") {
            operatorStack.push(tmpToken);
        }
        else if (tmpToken == ")") {
            while (stackTopWithCheck() != "(" && !operatorStack.empty()) {
                if (!performStackComputation(stackTopWithCheck())) {
                    return -666;
                }
                stackPopWithCheck();
            }
            if (!operatorStack.empty()) {
                stackPopWithCheck();
            }
            else {
                cerr << "Check whether your brackets placed correctly" << endl;
                return -666;
            }
        }
        else {
            cerr << "Unrecognized token: " << tmpToken << endl;
            return -666;
        }
    }
    while (!operatorStack.empty()) {
        if (stackTopWithCheck() == "(" || stackTopWithCheck() == ")") {
            cerr << "Check whether your brackets placed correctly" << endl;
            return -666;
        }
        if (!performStackComputation(stackTopWithCheck())) {
            return -666;
        }
        stackPopWithCheck();
    }
    return computeStack.top();
}

//Checks whether token is number
bool Calc::isNumber(string strToCheck) {
    bool ret = true;
    for (char i: strToCheck) {
        if (!('0' <= i && i <= '9')) {
            ret = false;
            break;
        }
    }
    return ret;
}

//Checks whether token is operator
int Calc::isOperator(string strToCheck) {
    if (strToCheck == "*" || strToCheck == "/" || strToCheck == "%") {
        return 1;
    }
    else if (strToCheck == "+" || strToCheck == "-") {
        return 0;
    }
    else {
        return -1;
    }
}

//Checks if operatorStack is empty and returns top element of it if not
string Calc::stackTopWithCheck() {
    if (!operatorStack.empty()) {
        return operatorStack.top();
    }
    else {
        return "";
    }
}

//Pops element from operatorStack only if it is not empty
void Calc::stackPopWithCheck() {
    if (!operatorStack.empty()) {
        operatorStack.pop();
    }
}

//Does basic rpn stack computation returns false if there was division by zero
bool Calc::performStackComputation(string oper) {
    int a = 0, b = 0;
    b = computeStack.top();
    computeStack.pop();
    a = computeStack.top();
    computeStack.pop();
    if (oper == "+") {
        computeStack.push(a + b);
    }
    else if (oper == "-") {
        computeStack.push(a - b);
    }
    else if (oper == "*") {
        computeStack.push(a * b);
    }
    else if (oper == "/") {
        if (b == 0) {
            cerr << "Division by zero" << endl;
            return false;
        }
        computeStack.push(a / b);
    }
    else if (oper == "%") {
        computeStack.push(a % b);
    }
    return true;
}