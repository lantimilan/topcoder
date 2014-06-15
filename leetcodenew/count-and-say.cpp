/**
* count-and-say.cpp
* https://oj.leetcode.com/problems/count-and-say/
*
*/
class Solution {
public:
    string countAndSay(int n) {
        string s = "1";
        for (int i = 2; i <= n; ++i) {
            string next;
            int start, end;
            int n = s.size();
            for (start = 0; start < n; start = end) {
                char ch = s[start];
                for (end = start+1; end < n && s[end] == ch; ++end) ;
                int cnt = end - start;
                next += tostring(cnt) + ch;
            }
            s = next;
        }
        return s;
    }
    string tostring(int n) {
        ostringstream oss; oss << n;
        return oss.str();
    }
};
