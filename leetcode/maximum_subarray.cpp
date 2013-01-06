class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ans, curr;
        ans = A[0];
        curr = 0;
        for (int i=0; i<n; ++i) {
            curr += A[i];
            ans = max(ans, curr);
            if (curr < 0) curr = 0;
        }
        return ans;
    }
};
