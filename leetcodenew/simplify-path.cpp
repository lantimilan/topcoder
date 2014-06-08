/**
* simplify-path.cpp
* https://oj.leetcode.com/problems/simplify-path/
*
* In leetcode OJ, Output limit exceeded could mean either TLE or MLE
*/
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st = split(path);
        string simplepath = getpath(st);
        return simplepath;
    }

    string getpath(stack<string> &st) {
        if (st.empty()) return "/";
        stack<string> st2;
        while (!st.empty()) {
            st2.push(st.top()); st.pop();
        }
        string path;
        while (!st2.empty()) {
            string token = st2.top(); path += "/" + token;
            st2.pop();
        }
        return path;
    }

    stack<string> split(string s) {
        stack<string> st;
        int start, end;
        for (start = 0; start < s.size(); start = end) {
            for (end = start + 1; end < s.size() && s[end] != '/'; ++end) ;
            string token = s.substr(start+1, end - start - 1);
            if (!token.empty()) {
                if (token == ".") {}  // ignore
                else if (token == "..") { if (!st.empty()) st.pop(); }
                else st.push(token);
            }
        }
        return st;
    }
};
