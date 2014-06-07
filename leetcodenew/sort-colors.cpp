/**
* sort-colors.cpp
* https://oj.leetcode.com/problems/sort-colors/
*
*/
class Solution {
public:
    void sortColors(int A[], int n) {
        // it is easier to imagine A[] has two fictious elements
        // it has 0 at A[-1] and it has 2 at A[n]
        // now we maintain the following invariants
        // [0..one) contains 0 only
        // [one..pos) contains 1 only
        // [two..n) contains 2 only
        //
        // pos points to an unknown element
        // by definition, one <= pos
        int one, two, pos;
        one = pos = 0; two = n;
        for (; pos < two; ) {
            int val = A[pos];
            if (val == 0) swap(A[pos++], A[one++]);
            if (val == 1) ++pos;
            if (val == 2) swap(A[pos], A[--two]);
        }
    }
};
