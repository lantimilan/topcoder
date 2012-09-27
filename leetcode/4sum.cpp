
bool operator<(const vector<int> &v1, const vector<int> &v2) {
    for(int i=0; i<(int)v1.size(); ++i) {
        if ((int)v2.size() < i+1) return false;
        if (v1[i] != v2[i]) return v1[i] < v2[i];
    }
    return false;
}

class Solution {
 public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector<vector<int> > ans;
        int n = num.size();
        if (n<4) return ans;

        sort(num.begin(), num.end());
        for(int i=0; i<n; ++i)
        for(int j=0; j<n; ++j) if (i!=j)
        {
        int pre = num[i] + num[j];
        for(int k=0, a=n-1; k<n && a>=0; ) 
        if (i!=k && j!=k)
        {
            int sum = pre + num[k];
            if (a!=i && a!=j && a!=k)
            {
                if (num[a] + sum == target) {
                    vector<int> v(4);
                    v[0] = num[i];
                    v[1] = num[j];
                    v[2] = num[k];
                    v[3] = num[a];
                    sort(v.begin(), v.end());
                    ans.push_back(v);
                    if (a>0 && num[a-1] == num[a]) a--;
                    else if (k+1<n && num[k+1] == num[k]) k++;
                    else { a--; k++; }
                } else if (num[a] + sum > target) {
                    a--;
                } else {
                    k++;
                }
            } else a--;
        } else k++;
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
};

// O(n^3) Accepted
//
// O(n^2 logn)
// sort then compute pair sums and merge
// cannot figure out how to avoid using the same element twice
//
// O(n^4 logn) TLE
