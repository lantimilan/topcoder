/**
* merge-sorted-array.cpp
* https://oj.leetcode.com/problems/merge-sorted-array/
*
* use i and j to track A[] and B[]
* pos to insert is i+1 + j+1 - 1
* since A[0..i] has i+1 elements
* and B[0..j] has j+1 elements
*/
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        for (int i = m-1, j = n-1; i >= 0 || j >= 0; ) {
            int pos = i + j + 1;
            if (i >= 0 && j >= 0) {
                if (A[i] > B[j]) A[pos] = A[i--];
                else A[pos] = B[j--];
            } else if (i >= 0) {
                A[pos] = A[i--];
            } else {
                A[pos] = B[j--];
            }
        }
    }
};
