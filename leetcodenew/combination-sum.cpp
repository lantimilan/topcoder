/**
* combination-sum.cpp
* https://oj.leetcode.com/problems/combination-sum/
*/
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        int n = candidates.size();
        int T = target;
        vector<vector<int> > dp(n+1, vector<int>(T+1));
        vector<vector<vector<int> > > pre(n+1, vector<vector<int> >(T+1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        for (int t = 0; t <= T; ++t) {
            if (dp[i-1][t]) {
                dp[i][t] = 1; pre[i][t].push_back(t);
            }
            if (t >= candidates[i-1]) {
                int p = t - candidates[i-1];
                if (dp[i][p]) {
                    dp[i][t] = 1; pre[i][t].push_back(p);
                }
            }
        }
        if (!dp[n][target]) return vector<vector<int> >();
        vector<vector<int> > ans = construct(target, n, pre, candidates);
        return ans;
    }

    vector<vector<int> > construct(int val, int l, const vector<vector<vector<int> > > &pre, const vector<int> &C) {
        if (l == 0) return vector<vector<int> > (1, vector<int>());
        vector<vector<int> > ans;
        for (int i = 0; i < pre[l][val].size(); ++i) {
            int t = pre[l][val][i];
            vector<vector<int> > prev;
            if (t == val) {
                prev = construct(t, l-1, pre, C);
                for (int i = 0; i < prev.size(); ++i) {
                    vector<int> v = prev[i];
                    ans.push_back(v);
                }
            } else {
                prev = construct(t, l, pre, C);
                for (int i = 0; i < prev.size(); ++i) {
                    vector<int> v = prev[i];
                    v.push_back(C[l-1]);
                    ans.push_back(v);
                }
            }
        }
        return ans;
    }
};
