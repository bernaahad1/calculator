#pragma once

#include <string>

using namespace std;

bool isOperand(const char ch);
bool isOperator(const char ch);
void doOperation(const double leftOp, const double rightOp, const char ch, double& result);
void calculate(const string& expression, double& result);
