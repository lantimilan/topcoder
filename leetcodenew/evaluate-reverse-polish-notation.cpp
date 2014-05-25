// evaluate-reverse-polish-notation.cpp
// https://oj.leetcode.com/problems/evaluate-reverse-polish-notation/
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        // for each token
        // if number, push to stack
        // if operator, pop two numbers in stack and do op
        // CAREFUL for minus and div, order are important
        stack<int> st;
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i].length() == 1) {
                int op1, op2;
                switch (tokens[i][0]) {
                    case '+':
                        op1 = st.top(); st.pop();
                        op2 = st.top(); st.pop();
                        st.push(op2 + op1);
                        break;
                    case '-':
                        op1 = st.top(); st.pop();
                        op2 = st.top(); st.pop();
                        st.push(op2 - op1);
                        break;
                    case '*':
                        op1 = st.top(); st.pop();
                        op2 = st.top(); st.pop();
                        st.push(op2 * op1);
                        break;
                    case '/':
                        op1 = st.top(); st.pop();
                        op2 = st.top(); st.pop();
                        st.push(op2 / op1);
                        break;
                    default:  // single digit number, 0 to 9
                        st.push(atoi(tokens[i].c_str()));
                        break;
                }
            } else {
                st.push(atoi(tokens[i].c_str()));
            }
        }
        return st.top();
    }
};

