class Solution {
public:
    // k is 0-based
    int findkth(int A[], int m, int B[], int n, int k) {
        int l1, r1, l2, r2;
        l1 = 0; r1 = m; l2 = 0, r2 = n;
        
        // since k is 0-based, there are k+1 elements
        // need to have non-empty (k+1)/2 and (k+1)/2 in
        // both arrays, so k>0
        // last element is at index mid1-1 and mid2-1
        while (l1 < r1 && l2 < r2) {
            int mid1, mid2;
            mid1 = min(l1+(k+1)/2, r1);
            mid2 = min(l2+(k+1)/2, r2);
            if (k==0) return min(A[l1], B[l2]);
            if (A[mid1-1] < B[mid2-1]) {  // throw away left of A[l1..r1]
                k -= (mid1-l1);
                l1 = mid1;
            } else {  // throw away left of B[l2..r2]
                k -= (mid2-l2);
                l2 = mid2;
            }
        }
        if (l1 < r1) return A[l1 + k];
        else return B[l2 + k];
    }
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lower, upper;
        // for m+n odd, it is (m+n)/2 and (m+n)/2
        // for m+n even, it is (m+n)/2-1 and (m+n)/2
        lower = findkth(A, m, B, n, (m+n-1)/2);
        upper = findkth(A, m, B, n, (m+n)/2);
        return (lower + upper) / 2.0;
    }
};
