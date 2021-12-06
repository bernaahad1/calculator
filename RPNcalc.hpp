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
* <file with helper functions that calculate the expression>
*
*/

#pragma once

#include <string>

using namespace std;

bool isOperand(const char ch);
bool isOperator(const char ch);
void doOperation(const double leftOp, const double rightOp, const char ch, double& result);
void calculate(const string& expression, double& result);
