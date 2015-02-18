#include "Calc.h"

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
                performStackComputation(stackTopWithCheck());
                stackPopWithCheck();
            }
            operatorStack.push(tmpToken);
        }
        else if (tmpToken == "(") {
            operatorStack.push(tmpToken);
        }
        else if (tmpToken == ")") {
            while (stackTopWithCheck() != "(" && !operatorStack.empty()) {
                performStackComputation(stackTopWithCheck());
                stackPopWithCheck();
            }
            if (!operatorStack.empty()) {
                stackPopWithCheck();
            }
            else {
                throw runtime_error("Brackets placed incorrectly");
            }
        }
        else {
            throw runtime_error("Unrecognized token: " + tmpToken);
        }
    }
    while (!operatorStack.empty()) {
        if (stackTopWithCheck() == "(" || stackTopWithCheck() == ")") {
            throw runtime_error("Brackets placed incorrectly");
        }
        performStackComputation(stackTopWithCheck());
        stackPopWithCheck();
    }
    return computeStack.top();
}

bool Calc::isNumber(string token) {
    bool ret = true;
    for (char i: token) {
        if (!('0' <= i && i <= '9')) {
            ret = false;
            break;
        }
    }
    return ret;
}

int Calc::isOperator(string token) {
    if (token == "*" || token == "/" || token == "%") {
        return 1;
    }
    else if (token == "+" || token == "-") {
        return 0;
    }
    else {
        return -1;
    }
}

string Calc::stackTopWithCheck() {
    if (!operatorStack.empty()) {
        return operatorStack.top();
    }
    else {
        return "";
    }
}

void Calc::stackPopWithCheck() {
    if (!operatorStack.empty()) {
        operatorStack.pop();
    }
}


void Calc::performStackComputation(string oper) {
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
            throw runtime_error("Division by zero");
        }
        computeStack.push(a / b);
    }
    else if (oper == "%") {
        computeStack.push(a % b);
    }
}