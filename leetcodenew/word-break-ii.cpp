// word-break-ii.cpp
// https://oj.leetcode.com/problems/word-break-ii/
//
class Solution {
public:
    map<int, vector<string> > memo;

    vector<string> wordBreak(string s, unordered_set<string> &dict) {
        // use recursion with memorization might be easier
        memo.clear();
        return helper(s, s.size(), dict);
    }

    vector<string> helper(string s, int len, unordered_set<string> &dict) {
        if (memo.count(len)) return memo[len];
        if (len == 0) return vector<string>(1, "");
        vector<string> ans;
        for (int prev = 0; prev < len; ++prev) {
            string sub = s.substr(prev, len - prev);
            if (dict.count(sub)) {
                vector<string> vec = helper(s, prev, dict);
                for (int i = 0; i < vec.size(); ++i) {
                    string sentence = vec[i];
                    if (!sentence.empty()) sentence += " " + sub;
                    else sentence = sub;
                    ans.push_back(sentence);
                }
            }
        }
        return memo[len] = ans;
    }
};
