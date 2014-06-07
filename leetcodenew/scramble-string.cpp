/**
* scramble-string.cpp
* https://oj.leetcode.com/problems/scramble-string/
*
*/
class Solution {
public:
    map<pair<string, string>, bool> memo;

    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) return false;
        if (s1.empty()) return true;
        if (s1.length() == 1) return s1[0] == s2[0];

        pair<string, string> p = make_pair(s1, s2);
        if (memo.count(p)) return memo[p];

        int n = s1.length();
        for (int l = 1; l < n; ++l) {
            string x1 = s1.substr(0, l);
            string y1 = s1.substr(l, n);
            string x2 = s2.substr(0, l);
            string y2 = s2.substr(l, n);
            if (isScramble(x1, x2) && isScramble(y1, y2)) return memo[p] = true;
            x2 = s2.substr(n-l, n);
            y2 = s2.substr(0, n-l);
            if (isScramble(x1, x2) && isScramble(y1, y2)) return memo[p] = true;
        }
        return memo[p] = false;
    }
};
