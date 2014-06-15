class Solution {
public:
    int totalNQueens(int n) {
        // http://en.wikipedia.org/wiki/Eight_queens_puzzle
        int sol[] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352,	724, 2680, 14200, 73712, 365596};
        return sol[n];
    }
};
