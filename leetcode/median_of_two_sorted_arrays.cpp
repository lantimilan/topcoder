class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int lower_median = findkth((m+n+1)/2, nums1, nums2);
        int upper_median = findkth((m+n)/2+1, nums1, nums2);
        cout << lower_median << ' ' << upper_median << endl;
        return (lower_median + upper_median) / 2.0;
    }
    
    int findkth(int k, vector<int>& nums1, vector<int>& nums2) {
        int ans;
        if (bsearch(k, nums1, nums2, ans)) return ans;
        if (bsearch(k, nums2, nums1, ans)) return ans;
        else assert(false);
    }
    
    bool bsearch(int k, vector<int>& src, vector<int>& dest, int& ans) {
        int m = src.size();
        int n = dest.size();
        int s = k;
        int lo = -1, hi = m;  // range is (lo, hi)
        while (lo+1 < hi) {  // invariant: mid is always valid index and range nonempty
            // cout << lo << ' ' << hi << endl;
            int x = (lo+hi)/2;  // make progress because lo < l < hi
            int l = x+1;
            int r = s - l;
            if (r < 0) {  // too many elements to the left of src[l-1]
                hi = x;
            } else if (r > n) {  // not enough elements to the left of src[l-1]
                lo = x;
            } else {
                if (r == 0) {
                    if (n == 0) {
                        ans = src[x]; return true;
                    } else if (src[x] <= dest[0]) {
                        ans = src[x]; return true;
                    } else {
                        // we need none from dest, but some dest elements are <= src[x]
                        // we need to search to the left of src[x]
                        hi = x;
                    }
                }
                // we need dest[r-1] <= src[l-1] <= (dest[r] or r == n)
                if (dest[r-1] > src[x]) {  // src[l-1] too small
                    lo = x;
                } else {
                    if (r >= n) {  // found kth, done
                        ans = src[x];
                        return true;
                    } else {
                        if (src[x] <= dest[r]) {
                            ans = src[x];
                            return true;
                        } else {  // src[l-1] too big
                            hi = x;
                        }
                    }
                }
            }
        }
        return false;
    }
};
