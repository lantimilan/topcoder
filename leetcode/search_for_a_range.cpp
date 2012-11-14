class Solution {
public:
    int lower(int A[], int n, int target) {
        // lower_bound
        int l, r;
        l = -1; r = n;
        // invariant: A[l] < target and A[r] >= target
        while (l+1 < r) {
            int m = (l+r)/2;  // l < m < r and m is a valid index
            if (A[m] < target) l = m;
            else r = m;
        }
        if (r < n && A[r] == target) return r;
        else return -1;
    }
    
    int upper(int A[], int n, int target) {
        int l, r;
        l = -1; r = n;
        // invariant: A[l] <= target and A[r] > target
        while (l+1 < r) {
            int m = (l+r) / 2;
            if (A[m] <= target) l = m;
            else r = m;
        }
        if (0<= l && A[l] == target) return l;
        else return -1;
    }
    vector<int> searchRange(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> ans(2);
        ans[0] = lower(A, n, target);
        ans[1] = upper(A, n, target);
        return ans;
    }
};

// lower_bound
// upper_bound
// 
// advanced binary search