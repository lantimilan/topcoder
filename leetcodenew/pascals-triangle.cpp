/**
* pascals-triangle.cpp
* https://oj.leetcode.com/problems/pascals-triangle/
*
*/
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > pascal;
        if (numRows == 0) return pascal;
        pascal.push_back(vector<int>(1,1));
        for (int i = 1; i < numRows; ++i) {
            vector<int> row;
            row.push_back(1);
            for (int j = 1; j < i; ++j) {
                int val = pascal[i-1][j-1] + pascal[i-1][j];
                row.push_back(val);
            }
            row.push_back(1);
            pascal.push_back(row);
        }
        return pascal;
    }
};
