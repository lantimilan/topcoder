class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        vector<int> table[2];        
        
        int n = rowIndex;        
        for (int i=0; i<2; ++i) table[i].resize(n+1);
        table[0][0] = 1;
        
        for (int i=1; i<=n; ++i) {
            int curr = i&1;
            int pre = 1-curr;
            
            table[curr][0] = 1;
            for (int j=1; j<=i; ++j) {
                table[curr][j] = table[pre][j] + table[pre][j-1];
            }
        }
        return table[n&1];
    }
};
