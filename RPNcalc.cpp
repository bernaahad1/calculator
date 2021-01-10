/**
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Berna Ahad
* @idnumber 62543
* @compiler VC
*
* <file with helper functions>
*
*/


#include "RPNcalc.h"
#include <iostream>
#include <stack>
#include <string>


using namespace std;

bool isOperand(const char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(const char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

void doOperation(const double leftOp, const double rightOp, const char ch, double& result) {
    switch (ch) {
    case '+':
        result = leftOp + rightOp;
        return;
    case '-':
        result = leftOp - rightOp;
        return;
    case '*':
        result = leftOp * rightOp;
        return;
    case '/':
        result = leftOp / rightOp;
        return;
    case '^':
        result = pow(leftOp, rightOp);
        return;
    }
    return;
}

void calculate(const string& expression, double& result) {
    stack <double> stack;

    for (size_t i = 0; i < expression.size(); i++) {

        if (isOperand(expression[i])) {
            double operand = (double)(expression[i]) - '0';

            while (expression[i + 1] != ' ') {
                operand = operand * 10 + ((double)(expression[i + 1]) - '0');

                ++i;
            }

            stack.push(operand);
        }
        else if (expression[i] == '-' && isOperand(expression[i + 1])) {
            double operand = ((double)(expression[i + 1]) - '0');
            ++i;

            while (expression[i + 1] != ' ') {
                operand = operand * 10 + ((double)(expression[i + 1]) - '0');
                ++i;
            }

            operand *= (-1);
            stack.push(operand);
        }
        else if (isOperator(expression[i])) {
            double leftOp = 0;
            double rightOp = 0;
            double curResult = 0;
            rightOp += stack.top();
            stack.pop();

            if ((!stack.empty()) && stack.top() != '#') {
                leftOp += stack.top();
                stack.pop();
            }

            doOperation(leftOp, rightOp, expression[i], curResult);

            if (curResult == INFINITY) {
                cout << "NaN" << endl;
                return;
            }
            if (rightOp == 0 && expression[i] == '/') {
                cout << "NaN" << endl;
                return;
            }

            stack.push(curResult);
        }
    }

    result = stack.top();
    cout << result << endl;
    return;
}
