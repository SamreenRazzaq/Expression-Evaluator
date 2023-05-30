#include <iostream>
#include <stack>
#include <string>

using namespace std;

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }
    return -1;
}

string infixToPostfix(string expression) {
    string result = "";
    stack<char> s;
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            result += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                result += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() != '(') {
                return "Invalid Expression";
            } else {
                s.pop();
            }
        } else {
            while (!s.empty() && precedence(c) <= precedence(s.top())) {
                result += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        result += s.top();
        s.pop();
    }
    return result;
}

int evaluatePostfix(string expression) {
    stack<int> s;
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            s.push(c - '0');
        } else {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            switch (c) {
                case '+':
                    s.push(operand1 + operand2);
                    break;
                case '-':
                    s.push(operand1 - operand2);
                    break;
                case '*':
                    s.push(operand1 * operand2);
                    break;
                case '/':
                    s.push(operand1 / operand2);
                    break;
               
            }
        }
    }
    return s.top();
}

int main() {
	
    string expression;
    cout<< "Enter The infix expression : ";
    getline(cin,expression);
    string postfix = infixToPostfix(expression);
    cout << "Postfix expression: " << postfix << endl;
    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;
    return 0;
}
