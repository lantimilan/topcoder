#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    map<pair<int,int>, vector<vector<int> > > memo;

    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        int n = num.size();
        int T = target;
        vector<vector<int> > dp(n+1, vector<int>(T+1));
        vector<vector<vector<int> > > pre(n+1, vector<vector<int> >(T+1, vector<int>()));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i)
        for (int t = 0; t <= T; ++t) {
            if (dp[i-1][t]) {
                dp[i][t] = 1;
                pre[i][t].push_back(t);
            }
            if (t >= num[i-1]) {
                int p = t - num[i-1];
                if (dp[i-1][p]) {
                    dp[i][t] = 1;
                    pre[i][t].push_back(p);
                }
            }
        }
        memo.clear();
        vector<vector<int> > ans;
        if (!dp[n][T]) return ans;
        ans = construct(target, n, pre, num);
        for (int i = 0; i < ans.size(); ++i) sort(ans[i].begin(), ans[i].end());
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }

    vector<vector<int> > construct(int target, int n, const vector<vector<vector<int> > > &pre, const vector<int> &num) {
        if (n == 0) return vector<vector<int> >(1, vector<int>());
        //if (memo.count(make_pair(target, n))) return memo[make_pair(target, n)];
        vector<vector<int> > ans;
        for (int i = 0; i < pre[n][target].size(); ++i) {
            int p = pre[n][target][i];
            vector<vector<int> > prev;
            if (p == target) {
                prev = construct(p, n-1, pre, num);
                for (int i = 0; i < prev.size(); ++i) ans.push_back(prev[i]);
            } else {
                prev = construct(p, n-1, pre, num);
                for (int i = 0; i < prev.size(); ++i) {
                    vector<int> v = prev[i]; v.push_back(num[n-1]);
                    ans.push_back(v);
                }
            }
        }
        return memo[make_pair(target, n)] = ans;
    }
};

int main()
{
    Solution sol;
    int a[] = {13,23,25,11,7,26,14,11,27,27,26,12,8,20,22,34,27,17,5,26,31,11,16,27,13,20,29,18,7,14,13,15,25,25,21,27,16,22,33,8,15,25,16,18,10,25,9,24,7,32,15,26,30,19};
    vector<int> vec(a, a + sizeof(a)/sizeof(a[0]));
    int target = 25;
    vector<vector<int> > ans = sol.combinationSum2(vec, target);
    for (int i = 0; i < ans.size(); ++i) {
        for (int j = 0; j < ans[i].size(); ++j) cout << ans[i][j] << ' ';
        cout << endl;
    }
}
