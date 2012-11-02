class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int i, j, k;
        for (i=m-1, j=n-1, k=m+n-1; i>=0 && j>=0; ) {
            if (A[i] > B[j]) { A[k--] = A[i--]; }
            else { A[k--] = B[j--]; }
        }
        for (; i>=0; --i) { A[k--] = A[i]; }
        for (; j>=0; --j) { A[k--] = B[j]; }
    }
};