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


#include "convert_to_postfix.h"

#include <iostream>
#include <string>
#include <stack>

using namespace std;

//here, precedence() function is used to define the precedence to the operator.
int precedence(const char op) {

    if (op == '+' || op == '-')                   /* it defines the lowest precedence */
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')                                /* exponent operator has the highest precedence */
        return 3;

    return 0;
}

/* The eqlOrhigher() function is used to check the higher or equal precedence of the two operators in infix expression. */
bool eqlOrHigher(const char operator1, const char operator2) {
    int p1 = precedence(operator1);
    int p2 = precedence(operator2);
    if (p1 == p2) {
        if (operator1 == '^') {
            return false;
        }
        return true;
    }
    return  (p1 > p2 ? true : false);
}

// The RPN() function converts the expression from infix to postfix
string RPN(const string& infix) {
    stack <char> st;
    string postfix = "";
    char ch;

    st.push('#');

    for (size_t i = 0; i < infix.length(); i++) {

        ch = infix[i];

        if (ch == ' ') {
            continue;
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (isOperand(ch)) {
            int j = i + 1;
            postfix += ch;      // if the symbol is operand add it to the postfix and check if it has another numbers

            while (isOperand(infix[i + 1])) {
                postfix += infix[i + 1];
                i++;
            }
            postfix += ' ';
        }
        else if (isOperator(ch)) {
            bool isNegativeNum = false;

            if (ch == '-') {
                isNegativeNum = true;
                for (int j = i - 1; j >= 0; j--) {
                    if (infix[j] != '(' && infix[j] != ' ') {
                        isNegativeNum = false;
                    }
                    else if (infix[j] == '(' && isNegativeNum) {
                        break;
                    }
                }
                if (isNegativeNum) {
                    postfix += ch;
                    continue;
                }
            }
            while (!st.empty() && (st.top() != '#') && eqlOrHigher(st.top(), ch)) {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                postfix += ' ';
                st.pop();
            }
            st.pop();
        }
    }
    while (!st.empty() && st.top() != '#') {
        postfix += st.top();
        postfix += ' ';
        st.pop();
    }

    return postfix;
}
