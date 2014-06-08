/**
* spiral-matrix-ii.cpp
* https://oj.leetcode.com/problems/spiral-matrix-ii/
*
*/
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        vector<vector<int> > matrix(n, vector<int>(n));
        int len = n-1;

        int dir[][2] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};
        int val = 0;
        int srow, scol;
        srow = scol = 0;
        while (len > 0) {
            int row = srow, col = scol;
            for (int x = 0; x < 4; ++x) {
                for (int i = 0; i < len; ++i) {
                    matrix[row][col] = ++val;
                    row += dir[x][0]; col += dir[x][1];
                }
            }
            len -= 2; srow++; scol++;
        }
        if (len == 0) matrix[srow][scol] = ++val;
        return matrix;
    }
};
