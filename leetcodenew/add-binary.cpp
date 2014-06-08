/**
* add-binary.cpp
* https://oj.leetcode.com/problems/add-binary/
*
* bug: forgot to clear carry
*/
class Solution {
public:
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int n = max(a.length(), b.length());
        string sum(n, '0');
        int carry = 0;
        for (int i = 0; i < n; ++i) {
            int d1 = (i < a.length()) ? a[i] - '0' : 0;
            int d2 = (i < b.length()) ? b[i] - '0' : 0;
            int s = d1 + d2 + carry;
            if (s >= 2) {
                carry = 1; s -= 2;
            } else {
                carry = 0;
            }
            sum[i] = char(s + '0');
        }
        if (carry) sum.push_back('1');
        reverse(sum.begin(), sum.end());
        return sum;
    }
};
