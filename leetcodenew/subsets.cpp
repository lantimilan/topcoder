/**
* subsets.cpp
* https://oj.leetcode.com/problems/subsets/
*
*/
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        sort(S.begin(), S.end());
        vector<vector<int> > ans;
        int n = S.size();
        for (int mask = 0; mask < (1<<n); ++mask) {
            vector<int> vec;
            for (int i = 0; i < n; ++i) if (mask & 1<<i)
                vec.push_back(S[i]);
            ans.push_back(vec);
        }
        return ans;
    }
};
