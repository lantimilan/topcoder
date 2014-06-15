/**
* first-missing-positive.cpp
* https://oj.leetcode.com/problems/first-missing-positive/
*/
class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        for (int i = 0; i < n; ++i) {
            int k = A[i]; if (k <= 0) continue;
            while (1 <= k && k <= n && k != A[k-1]) {  // put k into A[k-1]
                int next = A[k-1];
                A[k-1] = k;
                k = next;
            }
        }
        for (int i = 0; i < n; ++i) if (A[i] != i+1) return i+1;
        return n+1;
    }
};
