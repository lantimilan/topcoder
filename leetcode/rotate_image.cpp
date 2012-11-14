class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        // start at i, and end at n-i (exclusive)
        // rotate the square (i,i) (i,n-i-1) (n-i-1, n-i-1) (n-i-1, i)
        int n;
        n = matrix.size();
        
        // i+2 <= n-i
        for (int i=0; 2*i + 2 <= n; ++i)        
        {
            // use four pointers
            int s[4][2];
            s[0][0] = i; s[0][1] = i;
            s[1][0] = i; s[1][1] = n-i-1;
            s[2][0] = n-i-1; s[2][1] = n-i-1;
            s[3][0] = n-i-1; s[3][1] = i;
            
            int dir[][2] = {
                {0, +1}, {+1, 0}, {0, -1}, {-1, 0}
            };
            for (int x=i; x<n-i-1; ++x) {
                // swap s[0..3];
                int v = matrix[s[3][0]][s[3][1]];
                for (int i=2; i>=0; --i) {
                    matrix[s[i+1][0]][s[i+1][1]] = matrix[s[i][0]][s[i][1]];
                }
                matrix[s[0][0]][s[0][1]] = v;
                for (int i=0; i<4; ++i)
                for (int j=0; j<2; ++j)
                    s[i][j] += dir[i][j];
            }
        }
    }
};
