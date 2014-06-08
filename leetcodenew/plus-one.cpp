/**
* plus-one.cpp
* https://oj.leetcode.com/problems/plus-one/
*/
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        vector<int> ans(digits.size());
        int carry = 1;
        reverse(digits);
        for (int i = 0; i < digits.size(); ++i) {
            int sum = digits[i] + carry;
            if (sum >= 10) {
                ans[i] = sum - 10; carry = 1;
            } else {
                ans[i] = sum; carry = 0;
            }
        }
        if (carry) ans.push_back(carry);
        reverse(ans);
        return ans;
    }

    void reverse(vector<int> &digits) {
        for (int i = 0, j = digits.size() - 1; i < j; ++i, --j) {
            int d = digits[i]; digits[i] = digits[j]; digits[j] = d;
        }
    }
};
