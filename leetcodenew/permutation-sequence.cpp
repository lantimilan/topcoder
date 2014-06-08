/**
* permutation-sequence.cpp
* https://oj.leetcode.com/problems/permutation-sequence/
*
* this one is interesting. generating permutations in order will TLE
* even though n is at most 9
* a small optimization is to decide leading digit, then got AC
*/
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> vec(n);
        for (int i = 0; i < n; ++i) vec[i] = i+1;
        k = (k-1) % fact(n);
        int t = fact(n-1), start = 1;
        while (k >= t) { start++; k -= t; }
        swap(vec[0], vec[start-1]);
        sort(vec.begin()+1, vec.end());
        while (k-- > 0) permute(vec);
        return vec2str(vec);
    }

    string vec2str(const vector<int> &vec) {
        string s(vec.size(), '0');
        for (int i = 0; i < vec.size(); ++i) s[i] = char(vec[i] + '0');
        return s;
    }

    int fact(int n) {
        int ans = 1;
        for (int i = 1; i <= n; ++i) ans *= i;
        return ans;
    }

    void permute(vector<int> &vec) {
        int n = vec.size();
        int i, j;
        for (i = n-1; i > 0; --i)
            if (vec[i] > vec[i-1]) break;
        for (j = n-1; j >= i; --j)
            if (vec[j] > vec[i-1]) break;
        swap(vec[i-1], vec[j]);
        reverse(vec.begin() + i, vec.end());
    }
};
