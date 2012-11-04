class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        vector<vector<int> > ans;
        if (numRows == 0) return ans;
        ans.push_back(vector<int>(1,1));
        for (int i=1; i<numRows; ++i) {
            vector<int> row;
            row.push_back(1);
            for (int j=1; j<=i; ++j) {
                int val = 0;
                if (0<=j-1 && j-1<=i-1) val += ans[i-1][j-1];
                if (0<=j && j<=i-1) val += ans[i-1][j];
                row.push_back(val);
            }
            ans.push_back(row);
        }
        return ans;
    }
};

// numRows can be zero
