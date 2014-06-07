/**
* combinations.cpp
* https://oj.leetcode.com/problems/combinations/
*
*/
class Solution {
public:
    map<pair<int,int>, vector<vector<int> > > memo;
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > empty, one(1, vector<int>());

        if (n < 0 || k < 0) return empty;
        if (n < k) return empty;
        if (n == 0) return one;
        pair<int, int> p = make_pair(n, k);
        if (memo.count(p)) return memo[p];
        vector<vector<int> > pre1 = combine(n-1, k);
        vector<vector<int> > pre2 = combine(n-1, k-1);
        for (int i = 0; i < pre2.size(); ++i) {
            pre2[i].push_back(n);
            pre1.push_back(pre2[i]);
        }
        return memo[p] = pre1;
    }
};
