#pragma once

#include <string>

using namespace std;

bool isOperator(const char ch);
bool isOperand(const char ch);
int precedence(const char op);
bool eqlOrHigher(const char operator1, const char operator2);
string RPN(const string& infix);
