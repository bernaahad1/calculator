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
* <main file>
*
*/


#include <iostream>
#include <fstream>
#include <string>
#include <stack>

#include "RPNcalc.h"
#include "convert_to_postfix.h"

using namespace std;

bool bracketsAreBalanced(const string& line);

bool correctSymb(const string& line, int i = 0, bool InNum = false, bool inSymb = false);

int main()
{
    string line;
    fstream file;
    string postfix_expression;
    double result = 0;

    file.open("aritmetic_expression.txt", ios::in);

    if (file.is_open()) {
        getline(file, line);
    }
    else {
        cout << "NaN" << endl;
    }

    file.close();

    if (bracketsAreBalanced(line) && correctSymb(line)) {
        postfix_expression = RPN(line);
        calculate(postfix_expression, result);
    }
    else {
        cout << "NaN";
    }

    return 0;
}

bool correctSymb(const string& line, int i, bool InNum, bool inSymb) {
    char ch = line[i];
    if (line[i] == '\0') {
        return InNum;    //end the function and if the last symbol is num return true else return false
    }
    if (ch == '(') {
        if (InNum) {
            return false;  //if before '(' is a numumber then return false
        }
        inSymb = false;
        InNum = false;
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (ch == ')') {
        if (inSymb) {   // check if before ')' is a symbol or number
            return false;
        }
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (isOperand(ch)) {
        if (i != 0 && line[i - 1] == ' ' && (i - 1) != 0 && InNum) {  // checking for icorrect input like "2  2"
            return false;
        }
        InNum = true;
        inSymb = false;
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (ch == ' ') {
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (isOperator(ch)) {
        if ((!InNum) && (!inSymb) && ch == '-') { // check if the beggining start with '-'
            inSymb = true;
            InNum = false;
            return correctSymb(line, ++i, InNum, inSymb);
        }
        if (!InNum) {
            return false;
        }
        inSymb = true;
        InNum = false;
        return correctSymb(line, ++i, InNum, inSymb);
    }

    return false;
}

bool bracketsAreBalanced(const string& line) {
    int numOfOp = 0; //number of the oppening brackets
    int numOfClos = 0; //number of the closing brackets

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == '(') {
            numOfOp++;
        }
        if (line[i] == ')') {
            numOfClos++;
        }
    }

    return numOfClos == numOfOp;
}
