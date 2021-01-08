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

using namespace std;

bool isOperator(char ch);

bool correctSymb(string line, int i = 0, bool InNum = false, bool inSymb = false);

bool bracketsAreBalanced(string line);

bool isOperand(char ch);

// here, precedence() function is used to define the precedence to the operator.  
int precedence(char op);

// The eqlOrhigher() function is used to check the higher or equal precedence of the two operators in infix expression. 
bool eqlOrHigher(char operator1, char operator2);

string RPN(string infix); 

void doOperation(const double leftOp, const double rightOp, const char ch, double& result);

void calculate(const string expression, double& result);


int main()
{
    string line;
    fstream file;
    string postfix_expression;
    double result = 0;

    file.open("aritmetic_expression.txt", ios::in);

    if (file.is_open()) {
        getline(file,line);
    }
    else {
        cout << "Problem with reading from the file!" << endl;
    }

    file.close();

    if (bracketsAreBalanced(line) && correctSymb(line)) {
          postfix_expression = RPN(line);
          calculate(postfix_expression, result);
          cout << result << endl;
    }
    else {
        cout << "The input data is invalid!";
    }

    return 0;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

bool correctSymb(string line, int i, bool InNum , bool inSymb) { 
    char ch = line[i];
    if (line[i] == '\0') {
        return InNum;               //end the function and if the last symbol is num return true else return false
    }
    if (ch == '(') {
        if (InNum) {
            return false;          //if before '(' is a numumber then return false
        }
        inSymb = false;
        InNum = false;
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (ch == ')') {
        if (inSymb) {              // check if before ')' is a symbol or number
            return false;
        }
        return correctSymb(line, ++i, InNum, inSymb);
    }
    if (ch >= '0' && ch <= '9') {
        if (i != 0 && line[i - 1] == ' ' && (i - 1) != 0 && InNum) {    // checking for icorrect input like "2  2"
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
        if ((!InNum) && (!inSymb) && ch == '-') {         // check if the beggining start with '-'
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

}

bool bracketsAreBalanced(string line) {
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

bool isOperand(char ch) {
    return (ch >= '0' && ch <= '9');
}

// here, precedence() function is used to define the precedence to the operator.  
int precedence(char op) {
    
    if (op == '+' || op == '-')                   /* it defines the lowest precedence */
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')                                /* exponent operator has the highest precedence */
        return 3;

    return 0;
}

/* The eqlOrhigher() function is used to check the higher or equal precedence of the two operators in infix expression. */
bool eqlOrHigher(char operator1, char operator2) {
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
string RPN(string infix) {
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
            postfix += ch;            // if the symbol is operand add it to the postfix and check if it has another numbers

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
                    if (infix[j] == '(' && isNegativeNum) {
                        postfix += ch;
                        break;
                    }
                }
                if (isNegativeNum) {
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

void calculate(const string expression, double& result) {
    stack <double> stack;

    for (size_t i = 0; i < expression.size(); i++) {
        if (isOperand(expression[i])) {
            double operand = (double)(expression[i]) - '0';

            while (expression[i + 1] != ' ') {
                operand = operand * 10 +((double) (expression[i + 1]) - '0');
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
                cout << "The result is too big!" << endl;
                return;
            }
            if (rightOp == 0 && expression[i] == '-') {
                cout << "The denominator is zero!" << endl;
                return;
            }
            stack.push(result);
        }
    }

    result = stack.top();
    return;
}
