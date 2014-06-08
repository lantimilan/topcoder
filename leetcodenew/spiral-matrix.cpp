/**
* spiral-matrix.cpp
* https://oj.leetcode.com/problems/spiral-matrix/
*
* is it possible to avoid mark[][]?
*
* similar idea can be used to solve spiral-matrix-ii
* start at (0,0) follow dir[x][] until hit boundary or some filled cell
* then change to dir[x+1][]
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector<int> vec; if (matrix.empty()) return vec;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int> > mark(m, vector<int>(n, 0));
        // right, down, left, up
        const int dir[][2] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};
        int r = 0, c = 0;
        int x = 0;
        for (int i = 0; i < m*n; ++i) {
            int val = matrix[r][c]; vec.push_back(val); mark[r][c] = 1;
            int r2 = r + dir[x][0], c2 = c + dir[x][1];
            if (inbound(r2, c2, m, n) && !mark[r2][c2]) { r = r2; c = c2; }
            else {
                x = x+1; if (x >= 4) x = 0;
                r += dir[x][0]; c += dir[x][1];
            }
        }
        return vec;
    }

    bool inbound(int r, int c, int m, int n) {
        return 0 <= r && r < m && 0 <= c && c < n;
    }
};
