#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int label[1500][1500];
int vis[1500][1500];

enum {
    UNKNOWN = 0,
    ROMAN = 1,
    PERSIAN = 2
};

int diff[6][2] = {
    {-1,0}, {-1, +1},
    {0,-1}, {0, +1},
    {+1,-1}, {+1, 0}
};

bool in_bound(int r, int c) {
    return 0 <= r && r < N && 0<= c && c < N;
}

bool dfs(int r, int c) {
    vis[r][c] = 1;
    for (int x = 0; x < 6; ++x) {
        int r2 = r + diff[x][0];
        int c2 = c + diff[x][1];
        if (in_bound(r2,c2) && label[r2][c2] == ROMAN) {
            if (c2 == N-1) return true;
            if (!vis[r2][c2]) {
                bool child = dfs(r2, c2);
                if (child) return true;
            }
        }
    }
    return false;
}

bool dfs2(int r, int c) {
    vis[r][c] = 1;
    for (int x = 0; x < 6; ++x) {
        int r2 = r + diff[x][0];
        int c2 = c + diff[x][1];
        if (in_bound(r2,c2) && label[r2][c2] == PERSIAN) {
            if (in_bound(r2,c2) && r2 == N-1) return true;
            if (!vis[r2][c2]) {
                // A subtle bug with copy/paste, dfs instead of dfs2
                bool child = dfs2(r2, c2);
                if (child) return true;
            }
        }
    }
    return false;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >> N >> M;
    for (int k = 0; k < M; ++k) {
        int u, v; cin >> u >> v; --u; --v;
        if (k & 1) {
            label[u][v] = PERSIAN;
        } else {
            label[u][v] = ROMAN;
        }
    }

    string ans = "NEITHER";
    memset(vis, 0, sizeof vis);
    for (int r = 0; r < N; ++r) if (!vis[r][0] && label[r][0] == ROMAN) {
        if (dfs(r,0)) {
            ans = "ROMANS";
            break;
        }
    }
    memset(vis, 0, sizeof vis);
    for (int c = 0; c < N; ++c) if (!vis[0][c] && label[0][c] == PERSIAN) {
        if (dfs2(0,c)) {
            ans = "PERSIANS";
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
// AC

