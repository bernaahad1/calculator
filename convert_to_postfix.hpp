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
* <file with helper functions that convert infix expression to postfix one>
*
*/

#pragma once

#include <string>

using namespace std;

bool isOperator(const char ch);
bool isOperand(const char ch);
int precedence(const char op);
bool eqlOrHigher(const char operator1, const char operator2);
string RPN(const string& infix);
