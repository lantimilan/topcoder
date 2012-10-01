class Solution {
 public:
    int threeSumClosest(vector<int> &num, int target) {
        assert((int)num.size() >= 3);
        int ans = num[0] + num[1] + num[2];
        sort(num.begin(), num.end());
        int n = num.size();
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<n; ++j) if (j!=i)
            {
                int two = num[i] + num[j];
                vector<int>::iterator low;
                low = lower_bound(num.begin(), num.end(), target-two);

                int pos;
                // use left
                pos = low-num.begin();
                if (pos) --pos;
                if (pos!=i && pos!=j) {
                    if (abs(num[pos] + two - target) < abs(ans - target)) {
                        ans = num[pos] + two;
                    }
                }
                // use right
                pos = low-num.begin();
                if (pos>=n) --pos;
                if (pos!=i && pos!=j) {
                    if (abs(num[pos] + two - target < abs(ans - target))) {
                        ans = num[pos] + two;
                    }
                }
            }
        }
        return ans;
    }
};

// Accepted
// O(n^2 logn)
//
// O(n^3) TLE
