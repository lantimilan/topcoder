class Solution {
public:
    void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int i, j, n;
        n = num.size();
        for (i=n-1; i>0; --i)
            if (num[i-1] < num[i]) break;
            ;
        if (i<=0) {
            reverse(num.begin(), num.end());
            return;
        }
        for (j=i; j<n; ++j)
            if (num[j] <= num[i-1]) break;
        swap(num[i-1], num[j-1]);
        reverse(num.begin()+i, num.end());
    }
};
