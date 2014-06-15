/**
* multiply-strings.cpp
* https://oj.leetcode.com/problems/multiply-strings/
*
* !! forget return causes RE
*/
class Solution {
public:
    string multiply(string num1, string num2) {
        // 1. reverse both numbers
        // 2. for each digit in num2, mult with num1, shift and add to ans
        if (num1 == "0" || num2 == "0") return "0";
        string ans(1, '0');
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        for (int i = 0; i < num2.size(); ++i) {
            int d = num2[i] - '0';
            string cur;
            int carry = 0;
            for (int j = 0; j < num1.size(); ++j) {
                int x = num1[j] - '0';
                int p = x * d + carry;
                carry = p / 10; p %= 10;
                cur += char(p + '0');
            }
            if (carry) cur += char(carry + '0');
            cur = string(i, '0') + cur;
            ans = add(ans, cur);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string add(string s1, string s2) {
        string ans;
        int carry = 0;
        for (int i = 0, j = 0; i < s1.size() || j < s2.size(); ++i, ++j) {
            int d1, d2; d1 = d2 = 0;
            if (i < s1.size()) d1 = s1[i] - '0';
            if (j < s2.size()) d2 = s2[j] - '0';
            int sum = d1 + d2 + carry;
            carry = sum / 10; sum %= 10;
            ans += char(sum + '0');
        }
        if (carry) ans += char(carry + '0');
        return ans;
    }

};
