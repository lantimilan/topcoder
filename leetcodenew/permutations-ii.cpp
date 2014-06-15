/**
* permutations-ii.cpp
* https://oj.leetcode.com/problems/permutations-ii/
*
*/
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > ans;
        if (num.size() <= 1) {
            ans.push_back(num); return ans;
        }
        sort(num.begin(), num.end());
        int n = num.size();
        int peak = n - 1;
        while (peak > 0) {
            ans.push_back(num);
            for (peak = n-1; peak-1 >= 0 && num[peak] <= num[peak-1]; --peak) ;
            if (peak <= 0) break;
            int pos;
            for (pos = n-1; pos >= peak; --pos) if (num[pos] > num[peak-1]) break;
            swap(num[pos], num[peak-1]);
            reverse(num.begin() + peak, num.end());
        }
        return ans;
    }
};
