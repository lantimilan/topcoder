/**
* gray-code.cpp
* https://oj.leetcode.com/problems/gray-code/
*
* Algorithm:
* start with 0 and 1, which is level 1
* level k+1 is obtained by prefix by 0 for every element in level k
* and prefix by 1 for the same set of elements, except reversed
*
* It is easy to prove by induction that the numbers thus constructed
* satisfy the property that adjacent two numbers differ by exactly 1 bit
*/
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ans;
        if (n == 0) {
            ans.push_back(0);
            return ans;
        }
        if (n == 1) {
            ans.push_back(0); ans.push_back(1);
            return ans;
        }
        vector<int> prefix = grayCode(n-1);
        ans = prefix;
        reverse(prefix.begin(), prefix.end());
        for (int i = 0; i < prefix.size(); ++i) {
            ans.push_back(prefix[i] | 1<<(n-1));
        }
        return ans;
    }
};
