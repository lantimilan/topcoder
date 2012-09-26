class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //
        typedef pair<int, int> pii;
        typedef pair<int, pii> piii;

        set<piii> tmp;
        int n = num.size();
        for(int i=0; i<n; ++i)
        for(int j=i+1; j<n; ++j)
        for(int k=j+1; k<n; ++k)
        {
            if (num[i] + num[j] + num[k] == 0)
            {
                vector<int> v(3);
                v[0] = num[i]; v[1] = num[j]; v[2] = num[k];
                sort(v.begin(), v.end());
                piii p = make_pair(v[0], pii(v[1], v[2]));
                tmp.insert(p);
            }
        }
        vector<vector<int> > ans;
        for(set<piii>::const_iterator cit = tmp.begin();
            cit != tmp.end(); ++cit) {
            vector<int> v(3);
            v[0] = cit->first;
            v[1] = cit->second.first;
            v[2] = cit->second.second;
            ans.push_back(v);
        }
        return ans;
    }
};

// Accepted
// O(n^3 logn)
