class Solution {
public:
    int jump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n<=1) return 0;
        
        int pos = 0;
        int last = A[pos];
        int ans = 1;
        while (last < n-1) {
            int next = 0;
            for (; pos <= last; ++pos)
                next = max(next, pos + A[pos]);
            last = next;
            ans++;
        }
        return ans;
    }
};