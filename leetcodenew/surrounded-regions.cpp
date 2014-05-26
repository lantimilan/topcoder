/**
* surrounded-regions.cpp
* https://oj.leetcode.com/problems/surrounded-regions/
*
* OJ seems to have some testcases causing recursive dfs to stackoverflow
* use bfs passed
* could also use dfs with explicit stack
*/
class Solution {
public:
    // unexplored node has board[i][j] == 'O'
    void bfs(int r, int c, vector<vector<char> > &board) {
        queue<pair<int,int> > que; que.push(make_pair(r, c)); board[r][c] = 'Z';
        int n = board.size();
        int m = board[0].size();
        while (!que.empty()) {
            pair<int,int> p = que.front(); que.pop();
            int r1, c1;
            r1 = p.first; c1 = p.second;
            const int dx[] = {-1, 0, +1, 0};
            const int dy[] = {0, +1, 0, -1};
            for (int dir = 0; dir < 4; ++dir) {
                int r2 = r1 + dx[dir];
                int c2 = c1 + dy[dir];
                if (0 <= r2 && r2 < n && 0 <= c2 && c2 < m) {
                    if (board[r2][c2] == 'O') {
                        board[r2][c2] = 'Z';
                        que.push(make_pair(r2, c2));
                    }
                }
            }
        }
    }
    void solve(vector<vector<char>> &board) {
        if (board.empty()) return;
        int n = board.size(), m = board[0].size();

        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        if (i == 0 || j == 0 || i == n-1 || j == m-1)
        if (board[i][j] == 'O')
            bfs(i, j, board);
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] == 'Z') board[i][j] = 'O';
            else if (board[i][j] == 'O') board[i][j] = 'X';
    }
};
