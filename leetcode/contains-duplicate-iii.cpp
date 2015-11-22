class Solution {

public:

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {

        multiset<int> st;

        int n = nums.size();

        int k2 = k+1;

        int w = min(n, k2);

        for (int i = 0; i < w; ++i) st.insert(nums[i]);

        

        if (n < 2) return false;

        if (k <= 0) return false;

        

        for (int i = 0; i < n; ++i) {

            multiset<int>::iterator it = st.find(nums[i]);

            if (check_tree(st, nums[i], t)) return true;

            st.erase(it);

            if (i+k2 < n) {

                st.insert(nums[i+k2]);

            }

        }

        return false;

    }

    

    bool check_tree(const multiset<int> &st, int val, int diff) {

        multiset<int>::iterator it = st.find(val); assert(it != st.end());

        multiset<int>::iterator next = it;

        if (++next != st.end()) {

            //cout << "next " << *next << ' ' << *it << endl;

            if (check_val(*next, *it, diff)) { return true; }

        }

        if (it != st.begin()) {

            multiset<int>::iterator pred = it;

            if (check_val(*--pred, *it, diff)) {

                //cout << "pred " << *pred << ' ' << *it << endl;

                return true; }

        }

        return false;

    }

    

    bool check_val(int a, int b, int diff) {

        return abs((long long)a-b) <= diff;

    }

};
