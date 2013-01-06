class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for(int i=0; i<n; ++i) 
        if (1<=A[i] && A[i]<=n)
        {
            if (A[i] == i+1) {
                // do nothing
            } else {
                while (A[i]>=1 && A[i] != A[A[i]-1]) {
                    swap(A[i], A[A[i]-1]);
                }    
            }                    
        }
        for(int i=0; i<n; ++i)
            if (A[i] != i+1)
                return i+1;
        return n+1;
    }
};