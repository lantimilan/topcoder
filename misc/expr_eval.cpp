// expr_eval.cpp
//
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

int get_prec(char ch)
{
    switch (ch) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: assert(false && "Invalid operator");
    }
    return -1;
}

int eval_simple(int a, int b, char op)
{
    switch (op) {
    case '+': return a+b;
    case '-': return a-b;
    case '*': return a*b;
    case '/': return a/b;  // check divide by zero
    }
    return 0;
}

int eval(const string &expr)
{
    stack<char> ops;
    stack<int> operands;

    istringstream iss(expr);
    string token;
    int ans = 0;
    while (iss >> token) {
        int pos = token.find('_');
        if (pos == string::npos) {  // operator
            char op = token[0];
            while (!ops.empty()) {
                char prev_op = ops.top();
                if (get_prec(prev_op) >= get_prec(op)) {
                    int a, b, c;
                    b = operands.top(); operands.pop();
                    a = operands.top(); operands.pop();
                    ops.pop();
                    c = eval_simple(a, b, prev_op);
                    operands.push(c);
                } else { break; }
            }
            ops.push(token[0]);
        } else {
            int base = atoi(token.substr(pos+1).c_str());
            string num = token.substr(0,pos);
            int val = strtol(num.c_str(), NULL, base);
            operands.push(val);
        }
    }
    while (!ops.empty()) {
        int a, b, c;
        char op;
        b = operands.top(); operands.pop();
        a = operands.top(); operands.pop();
        op = ops.top(); ops.pop();
        c = eval_simple(a, b, op);
        operands.push(c);
    }
    assert(ops.empty());
    ans = operands.top();
    return ans;
}

int main()
{
    string expr;
    getline(cin, expr);
    int ans = eval(expr);
    cout << ans << endl;
}
