#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VV;

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
        if (n==1) {
            if (target % val == 0) {
                VI vec(target/val, val);
                ans.push_back(vec);
            }
        } else {
            VV prev = solve(cand, n-1, target);
            VV curr;
            if (target >= val)
                curr = solve(cand, n, target - val);
            for(int i=0; i<curr.size(); ++i)
                curr[i].push_back(val);
            for(int i=0; i<prev.size(); ++i)
                ans.push_back(prev[i]);
            for(int i=0; i<curr.size(); ++i)
                ans.push_back(curr[i]);
        }
        return ans;
    }

    vector<vector<int> > combinationSum(vector<int> &cand, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());
        int n = cand.size();
        seen = VV(n+1, VI(target+1, 0));
        memo = vector<vector<VV> >(n+1, vector<VV>(target+1));

        return solve(cand, n, target);
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
    int a[] = {2};
    int target = 1;
    VI va(a, a+sizeof(a)/sizeof(a[0]));
    VV ans = sol.combinationSum(va, target);
    //printf("%d\n", ans.size());
    print(ans);
}

// Accepted
