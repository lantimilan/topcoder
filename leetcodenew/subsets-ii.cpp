/**
* subsets-ii.cpp
* https://oj.leetcode.com/problems/subsets-ii/
*
*/
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(), S.end());
        vector<pair<int,int> > freq;
        int start, end;
        for (start = 0; start < S.size(); start = end) {
            int val = S[start];
            for (end = start+1; end < S.size() && S[end] == val; ++end)
                ;
            int cnt = end - start;
            freq.push_back(make_pair(val, cnt));
        }
        vector<vector<int> > subsets; subsets.push_back(vector<int>());
        for (int i = 0; i < freq.size(); ++i) {
            int val = freq[i].first;
            int cnt = freq[i].second;
            vector<vector<int> > next;
            for (int s = 0; s < subsets.size(); ++s) {
                // for each subset, add subset with 1..freq[i].second vals
                vector<int> v = subsets[s];
                next.push_back(v);
                for (int c = 1; c <= cnt; ++c) {
                    v.push_back(val);
                    next.push_back(v);
                }
            }
            subsets = next;
        }
        return subsets;
    }

};
