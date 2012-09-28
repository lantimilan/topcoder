#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VV;

bool myless(const VI &v1, const VI&v2) {
    for(int i=0; i<v1.size(); ++i) {
        if (i>=v2.size()) return false;
        if (v1[i] != v2[i]) return v1[i] < v2[i];
    }
    return false;
}

bool eq(const VI &v1, const VI &v2) {
    if (v1.size() != v2.size()) return false;
    for(int i=0; i<v1.size(); ++i)
        if (v1[i] != v2[i]) return false;
    return true;
}

class Solution {
public:
    VV seen;
    vector<vector<VV> > memo;

    VV solve(VI &cand, int n, int target) {
        if (seen[n][target]) return memo[n][target];
        //printf("solve %d %d\n", n, target);
        seen[n][target] = 1;
        VV &ans = memo[n][target];
        int val = cand[n-1]; //printf("val %d\n", val);
        if (target == 0) {
            ans.push_back(VI());
        } else if (n==1) {
            if (target == val) {
                VI vec(target/val, val);
                ans.push_back(vec);
            }
        } else {
            VV prev = solve(cand, n-1, target);
            VV curr;
            if (target >= val)
                curr = solve(cand, n-1, target - val);
            for(int i=0; i<curr.size(); ++i)
                curr[i].push_back(val);
            for(int i=0; i<prev.size(); ++i)
                ans.push_back(prev[i]);
            for(int i=0; i<curr.size(); ++i)
                ans.push_back(curr[i]);
        }
        return ans;
    }

    vector<vector<int> > combinationSum2(vector<int> &cand, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = cand.size();
        sort(cand.begin(), cand.end());
        seen = VV(n+1, VI(target+1, 0));
        memo = vector<vector<VV> >(n+1, vector<VV>(target+1));

        VV ans = solve(cand, n, target);
        sort(ans.begin(), ans.end(), myless);
        ans.erase(unique(ans.begin(), ans.end(), eq), ans.end());
        return ans;
    }
};

void print(const VV& vec)
{
    for(int i=0; i<vec.size(); ++i)
    {
        for(int j=0; j<vec[i].size(); ++j)
            printf("%d ", vec[i][j]);
        putchar('\n');
    }
}

int main()
{
    Solution sol;
    int a[] = {1, 1};
    int target = 1;
    VI va(a, a+sizeof(a)/sizeof(a[0]));
    VV ans = sol.combinationSum2(va, target);
    //printf("%d\n", ans.size());
    print(ans);
}

// Accepted
