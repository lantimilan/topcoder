class Solution {
public:
    int search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int l, r;
        l=0; r=n;
        while (l < r) {
            int m = (l+r)/2;
            if (A[m] == target) return m;
            if (A[l] <= A[m]) {
                if (A[l] <= target && target <= A[m])
                    r = m;
                else
                    l = m+1;
            } else {
                if (A[m] <= target && target <= A[r-1]) {
                    l = m+1;
                } else {
                    r = m;
                }
            }
        }
        if (l<n && A[l] == target) return l;
        else return -1;
    }
};

// [l,mid) and [mid,r), one of the two is monotonic for rotated sorted array