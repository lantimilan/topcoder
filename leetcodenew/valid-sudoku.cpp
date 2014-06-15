class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        int n = board.size(); if (n != 9) return false;
        int m = board[0].size(); if (m != 9) return false;
        int ans = 1;
        for (int i = 0; i < 9; ++i) {
            int good = validate(board, i, 0, i+1, 9);
            ans &= good;
        }
        for (int j = 0; j < 9; ++j) {
            int good = validate(board, 0, j, 9, j+1);
            ans &= good;
        }
        for (int i = 0; i < 9; i+=3)
        for (int j = 0; j < 9; j+=3) {
            int good = validate(board, i, j, i+3, j+3);
            ans &= good;
        }
        return ans;
    }
    
    bool validate(const vector<vector<char> > &board, int i1, int j1, int i2, int j2) {
        int cnt[10] = {0};
        for (int i = i1; i < i2; ++i)
        for (int j = j1; j < j2; ++j) {
            char ch = board[i][j];
            if (ch != '.') cnt[ch-'0']++;
        }
        for (int v = 1; v <= 9; ++v) if (cnt[v] > 1) return false;
        return true;
    }
};
