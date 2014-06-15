/**
* permutations.cpp
* https://oj.leetcode.com/problems/permutations/
*/
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        if (num.empty()) return vector<vector<int> >();
        sort(num.begin(), num.end());
        vector<vector<int> > perms;
        int n = num.size();
        if (n == 1) { perms.push_back(num); return perms; }
        int peak = n-1;
        while (peak > 0) {
            perms.push_back(num);
            for (peak = n-1; peak - 1 >= 0 && num[peak] < num[peak-1]; --peak) ;
            if (peak <= 0) break;
            int pos;
            for (pos = n-1; pos >= peak; --pos) if (num[pos] > num[peak-1]) break;
            swap(num[pos], num[peak-1]);
            reverse(num.begin() + peak, num.end());
        }
        return perms;
    }
};
