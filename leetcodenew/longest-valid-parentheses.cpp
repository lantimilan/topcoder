/**
* longest-valid-parentheses.cpp
* https://oj.leetcode.com/problems/longest-valid-parentheses/
*/
class Solution {
public:
    // use a stack to keep track of previous lparen
    // use a vector<Interval> for possible merge
    // actually the stack need only contain the pos of lparen, no need to store '('
    int longestValidParentheses(string s) {
        int maxlen = 0;
        int n = s.size();
        vector<pair<int, int> > vec;
        stack<pair<char, int> > st;  // paren, pos
        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            int pos = i;
            if (s[i] == '(') st.push(make_pair(s[i], pos));
            else {
                if (st.empty()) {}  // do nothing
                else {
                    int prev = st.top().second; st.pop();
                    pair<int, int> cur = make_pair(prev, pos);
                    while (!vec.empty()) {
                        if (contained(vec.back(), cur)) vec.pop_back();
                        else if (vec.back().second + 1 == prev) {  // concat with vec.back()
                            prev = vec.back().first; vec.pop_back();
                        } else break;  // disjoint
                    }
                    vec.push_back(make_pair(prev, pos));
                }
            }
        }
        for (int i = 0; i < vec.size(); ++i) {
            int len = vec[i].second - vec[i].first + 1;
            maxlen = max(maxlen, len);
        }
        return maxlen;
    }

    bool contained(pair<int, int> small, pair<int, int> large) {
        return large.first < small.first && small.second < large.second;
    }
};
