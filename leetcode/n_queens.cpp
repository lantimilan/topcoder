class Solution {
public:
    vector<string> render(const vector<int> &v)
    {
        int n = v.size();
        vector<string> ans(n, string(n, '.'));
        for (int i=0; i<n; ++i)
            ans[i][v[i]] = 'Q';
        return ans;
    }
    bool attack(const vector<int>& cols, int r)
    {
        for (int i=0; i<r; ++i) {
            if (cols[i] == cols[r]) return true;
            if (abs(r-i) == abs(cols[r] - cols[i])) return true;            
        }
        return false;
    }
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below        
        // DO NOT write int main() function
        vector<vector<string> > ans;
        vector<int> cols(n, 0);
        int r = 0;

        while (r >= 0) {
            while (cols[r] < n && attack(cols, r))
                cols[r]++;
            if (cols[r] >= n) {
                cols[r] = 0;
                r--; 
                if (r>=0) cols[r]++;
            } else {
                r++;
                if (r==n) {
                    ans.push_back(render(cols));
                    cols[--r]++;
                }
            }        
        }
        
        return ans;
    }
};