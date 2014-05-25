/**
* word-ladder.cpp
* https://oj.leetcode.com/problems/word-ladder/
*
*/
class Solution {
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        queue<string> que; que.push(start);
        map<string, int> dist_map;
        dist_map[start] = 1;
        while (!que.empty()) {
            string s = que.front(); que.pop();
            // we only change each position once
            // so 26 * n possible choices
            for (int i = 0; i < s.length(); ++i)
            for (char ch = 'a'; ch <= 'z'; ++ch) if (ch != s[i]) {
                string t = s;
                t[i] = ch;
                if (dict.count(t)) {
                    if (!dist_map.count(t)) {
                        dist_map[t] = dist_map[s] + 1;
                        que.push(t);
                        if (t == end) return dist_map[t];
                    }
                }
            }
        }
        return 0;
    }
};
