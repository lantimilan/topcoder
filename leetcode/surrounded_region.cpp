class Solution {
public:
    void dfs(char marker, int r, int c, vector<vector<char> > &board)
    {
        board[r][c] = marker;
        int n = board.size(), m = board[0].size();

        int d[][2] = {{-1,0}, {0,+1}, {+1,0}, {0,-1}};

        queue<pair<int,int> > que;
        que.push(make_pair(r,c));
        while (!que.empty()) {
            pair<int,int> p = que.front(); que.pop();
            int i = p.first, j = p.second;
            for (int x = 0; x < 4; ++x) {
                int i2, j2;
                i2 = i + d[x][0]; j2 = j + d[x][1];
                if (0 <= i2 && i2 < n && 0 <= j2 && j2 < m
                    && board[i2][j2] == 'O') {
                    board[i2][j2] = marker; que.push(make_pair(i2,j2));
                    }
            }
        }
        // judge does not like dfs
        /*
        for (int x=0; x<4; ++x) {
            int i = r + d[x][0];
            int j = c + d[x][1];            
            if (0 <= i && i < n && 0 <= j && j < m && board[i][j] == 'O') {
                dfs(marker, i, j, board);                
            }
        } */       
    }
        
    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (board.empty()) return;
        // start from border, mark all O, then set all other O to X
        int n = board.size(), m = board[0].size();
        const char marker = 'T';
        for (int j=0; j<m; ++j) {
            int i;
            i = 0; if (board[i][j] == 'O') dfs(marker, i, j, board);
            i = n-1; if (board[i][j] == 'O') dfs(marker, i, j, board);
        }
        for (int i=0; i<n; ++i) {
            int j;
            j = 0; if (board[i][j] == 'O') dfs(marker, i, j, board);
            j = m-1; if (board[i][j] == 'O') dfs(marker, i, j, board);
        }
        for (int i=0; i<n; ++i)
        for (int j=0; j<m; ++j)
            if (board[i][j] == marker) board[i][j] = 'O';
            else if (board[i][j] == 'O') board[i][j] = 'X';
    }
};
