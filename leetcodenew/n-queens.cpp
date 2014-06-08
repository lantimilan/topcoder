/**
* n-queens.cpp
* https://oj.leetcode.com/problems/n-queens/
*/
class Solution {
public:
    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > sol;
        int row, col;
        vector<int> vec(n);
        row = col = 0;
        while (row >= 0) {
            while (col < n && attack(row, col, vec)) col++;
            if (col >= n) { row--; col = vec[row] + 1; }
            else {
                vec[row] = col;
                if (row == n-1) { sol.push_back(getconf(vec)); col++; }  // record solution
                else { row++; col = 0; }  // work on next row
            }
        }
        return sol;
    }

    bool attack(int row, int col, const vector<int> &vec) {
        for (int i = 0; i < row; ++i) if (vec[i] == col) return true;
        for (int i = 0; i < row; ++i)
            if (abs(i - row) == abs(vec[i] - col)) return true;
        return false;
    }

    vector<string> getconf(const vector<int> &queens) {
        int n = queens.size();
        vector<string> conf(n, string(n, '.'));
        for (int i = 0; i < n; ++i) conf[i][queens[i]] = 'Q';
        return conf;
    }
};

