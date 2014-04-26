// Csmall.cpp
//
// R, C <= 5, brute force all 2^(R*C) configurations

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int vis[10][10];

const int INF = 1000000;
const int dx[] = {-1, 0, +1};
const int dy[] = {-1, 0, +1};
int R, C, M;

void dfs(int row, int col, const vector<vector<int> > & field)
{
    vis[row][col] = 1;
    for (int x = 0; x < 3; ++x)
    for (int y = 0; y < 3; ++y) {
        int rr = row + dx[x];
        int cc = col + dy[y];
        if (0 <= rr && rr < R && 0 <= cc && cc < C)
        if (field[rr][cc] != INF)
        if (!vis[rr][cc]) {
            if (field[rr][cc] == 0) dfs(rr, cc, field);
            else vis[rr][cc] = 1;
        }
    }
}

void print(const vector<string> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
        cout << vec[i] << endl;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": " << endl;;
    cin >> R >> C >> M;
    int n = R * C;

    // special case M + 1 == R * C
    if (M + 1 == R * C) {
        vector<string> vec(R, string(C, '*'));
        vec[R-1][C-1] = 'c';
        print(vec);
        return;
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        // generate mine field
        int minecnt = 0;
        vector<string> vec(R, string(C, '.'));
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
        if (1 << (i * C + j) & mask) {
            vec[i][j] = '*';
            minecnt++;
        }
        if (minecnt != M) continue;

        // count neighbor for each cell
        vector<vector<int> > field(R, vector<int>(C, INF));
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) if (vec[i][j] == '.') {
            int neighbor = 0;
            for (int x = 0; x < 3; ++x)
            for (int y = 0; y < 3; ++y) {
                int rr = i + dx[x];
                int cc = j + dy[y];
                if (0 <= rr && rr < R && 0 <= cc && cc < C) {
                    if (vec[rr][cc] == '*') neighbor++;
                }
            }
            field[i][j] = neighbor;
        }

        int srow, scol; srow = scol = -1;
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (field[i][j] == 0) {
                srow = i; scol = j;
            }

        if (srow < 0) continue;

        dfs(srow, scol, field);

        bool good = true;
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
        if (vec[i][j] == '.' && !vis[i][j])
            good = false;

        if (good) {
            vec[srow][scol] = 'c';
            print(vec);
            return;
        }
    }
    cout << "Impossible" << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}

