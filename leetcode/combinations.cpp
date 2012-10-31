class Solution {
public:
    vector<vector<int> > gen(int n, int k)
    {
        vector<vector<int> > ans;
        if (n < k) return ans;
        if (k==0) {
            ans.push_back(vector<int>());
            return ans;
        }

        vector<vector<int> > s1, s2;
        s1 = gen(n-1, k-1);
        s2 = gen(n-1, k);
        for(int i=0; i<s1.size(); ++i) {
            s1[i].push_back(n);
        }
        ans = s1;
        for(int i=0; i<s2.size(); ++i) {
            ans.push_back(s2[i]);
        }
        return ans;
    }
    vector<vector<int> > combine(int n, int k) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return gen(n,k);
    }
};)