/**
* word-ladder-ii.cpp
* https://oj.leetcode.com/problems/word-ladder-ii/
*
*/
class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        map<string, int> dist_map;
        map<string, vector<string> > pred_map;
        queue<string> que;
        que.push(start); dist_map[start] = 1;
        while (!que.empty()) {
            string s = que.front(); que.pop();
            for (int i = 0; i < s.length(); ++i)
            for (char ch = 'a'; ch <= 'z'; ++ch) if (ch != s[i]) {
                string t = s; t[i] = ch;
                if (dict.count(t)) {
                    if (dist_map.count(t)) {
                        if (dist_map[t] == dist_map[s] + 1) {
                            pred_map[t].push_back(s);
                        }
                    } else {  // first time hit t
                        dist_map[t] = dist_map[s] + 1;
                        pred_map[t] = vector<string>(1, s);
                        que.push(t);
                    }
                }
            }
        }
        vector<vector<string> > ans;
        if (!dist_map.count(end)) return ans;
        dfs(end, pred_map, ans, vector<string>());
        for (int i = 0; i < ans.size(); ++i) {
            reverse(ans[i].begin(), ans[i].end());
        }
        return ans;
    }

    void dfs(string t, map<string, vector<string> > &pred_map, vector<vector<string> > &vec, vector<string> prefix) {
        if (!pred_map.count(t)) {
            prefix.push_back(t); vec.push_back(prefix); return;
        }

        prefix.push_back(t);
        for (int i = 0; i < pred_map[t].size(); ++i) {
            string next = pred_map[t][i];
            dfs(next, pred_map, vec, prefix);
        }
    }
};
