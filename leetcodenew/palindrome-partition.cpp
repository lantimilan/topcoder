/**
* palindrome-partition.cpp
* https://oj.leetcode.com/problems/palindrome-partitioning/
*/
class Solution {
public:
    map<int, vector<vector<string> > > memo;
    vector<vector<string>> partition(string s) {
        memo.clear();
        return helper(s, s.length());
    }

    vector<vector<string> > helper(string s, int len) {
        if (memo.count(len)) return memo[len];
        if (len == 0) return vector<vector<string> >(1, vector<string>());
        vector<vector<string> > &ans = memo[len];
        for (int prev = 0; prev < len; ++prev) {
            string sub = s.substr(prev, len - prev);
            if (is_palindrome(sub)) {
                vector<vector<string> > vec = helper(s, prev);
                for (int i = 0; i < vec.size(); ++i) {
                    vector<string> prev_vec = vec[i];
                    prev_vec.push_back(sub);
                    ans.push_back(prev_vec);
                }
            }
        }
        return ans;
    }

    bool is_palindrome(string s) {
        for (int i = 0, j = s.length()-1; i < j; ++i, --j)
            if (s[i] != s[j]) return false;
        return true;
    }
};
