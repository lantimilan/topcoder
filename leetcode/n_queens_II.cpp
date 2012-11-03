class Solution {
public:
    inline bool attack(const vector<int>& cols, int r)
    {
        for (int i=0; i<r; ++i) {
            if (cols[i] == cols[r]) return true;
            if (abs(r-i) == abs(cols[r] - cols[i])) return true;            
        }
        return false;
    }
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below        
        // DO NOT write int main() function
        int ans = 0;
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
                    ans++;
                    cols[--r]++;
                }
            }        
        }
        
        return ans;
    }
};

// TLE for n=12
