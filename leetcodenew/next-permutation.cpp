/**
* next-permutation.cpp
* https://oj.leetcode.com/problems/next-permutation/
*/
class Solution {
public:
    void nextPermutation(vector<int> &num) {
        if (num.empty()) return;
        int last;
        int n = num.size();
        for (last = n-1; last > 0 && num[last] <= num[last-1]; --last) ;
        if (last <= 0) {
            reverse(num.begin(), num.end());
            return;
        }
        int prev = last - 1;
        int pos;
        for (pos = n-1; pos >= last; --pos) if (num[pos] > num[prev]) break;
        swap(num[prev], num[pos]);
        reverse(num.begin() + last, num.end());
    }
};
