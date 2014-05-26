/**
 * longest-consecutive-sequence.cpp
 * https://oj.leetcode.com/problems/longest-consecutive-sequence/
 * 
 */
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        unordered_set<int> exists;
        unordered_set<int> seen;
        for (int i = 0; i < num.size(); ++i) {
            exists.insert(num[i]);
        }
        int maxlen = 0;
        for (int i = 0; i < num.size(); ++i) if (!seen.count(num[i])) {
            int center = num[i]; seen.insert(center);
            int cnt = 1;
            for (int j = center-1; exists.count(j); --j) {
                cnt++; seen.insert(j);
            }
            for (int j = center+1; exists.count(j); ++j) {
                cnt++; seen.insert(j);
            }
            maxlen = max(maxlen, cnt);
        }
        return maxlen;
    }
};
