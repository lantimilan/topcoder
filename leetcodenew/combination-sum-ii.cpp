#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    map<pair<int,int>, vector<vector<int> > > memo;

    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        vector<int>::iterator it; for (it = num.begin(); it != num.end(); ++it) if (*it > target) break;
        num.erase(it, num.end());
        int n = num.size();
        int T = target;
        vector<vector<vector<vector<int> > > > dp(n+1, vector<vector<vector<int> > >(T+1));

        dp[0][0] = vector<vector<int> >(1, vector<int>());
        for (int i = 1; i <= n; ++i)
        for (int t = 0; t <= T; ++t) {
            if (!dp[i-1][t].empty()) {
                dp[i][t] = dp[i-1][t];
            }
            if (t >= num[i-1]) {
                int p = t - num[i-1];
                if (!dp[i-1][p].empty()) {
                    for (int x = 0; x < dp[i-1][p].size(); ++x) {
                        vector<int> v = dp[i-1][p][x];
                        v.push_back(num[i-1]);
                        dp[i][t].push_back(v);
                    }
                }
            }
            dedupe(dp[i][t]);
        }
        //memo.clear();
        //vector<vector<int> > ans;
        //if (!dp[n][T]) return ans;
        //ans = construct(target, n, pre, num);
        vector<vector<int> > ans = dp[n][T];
        return ans;
    }

    void dedupe(vector<vector<int> > &vv) {
        if (vv.empty()) return;
        for (int i = 0; i < vv.size(); ++i) sort(vv.begin(), vv.end());
        sort(vv.begin(), vv.end());
        vv.erase(unique(vv.begin(), vv.end()), vv.end());
    }
    /* recursion might be too expensive
    vector<vector<int> > construct(int target, int n, const vector<vector<vector<int> > > &pre, const vector<int> &num) {
        if (n == 0) return vector<vector<int> >(1, vector<int>());
        if (memo.count(make_pair(target, n))) return memo[make_pair(target, n)];
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
    */
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
