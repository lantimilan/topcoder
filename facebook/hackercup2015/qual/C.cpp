// C.cpp
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int r, c;
    int t;
    Node(int rr, int cc, int tt) : r(rr), c(cc), t(tt) { }
};

const int diff[][2] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};

char maze[105][105];
int state[105][105][4];  // row, col, time
int dist[105][105][4];
int M, N;

int getTurret(char ch)
{
    switch(ch) {
        case '^': return 0;
        case '>': return 1;
        case 'v': return 2;
        case '<': return 3;
        default: return -1;
    }
}

bool isTurret(int r, int c)
{
    return getTurret(maze[r][c]) >= 0;
}

bool isEmpty(char ch) {
    return ch == '.' || ch == 'S' || ch == 'G';
}

bool inBound(int r, int c) {
    return 0 <= r && r < M && 0 <= c && c < N;
}

void update(int& a, int b) {
    if (a < 0) a = b;
    else if (b >= 0 && a > b) a = b;
}

void bfs(int srow, int scol, int t) {
    // first move always allowed
    //if (state[srow][scol][t]) return;

    memset(dist, -1, sizeof dist);
    queue<Node> que;
    que.push(Node(srow, scol, t));
    dist[srow][scol][t] = 0;
    while (!que.empty()) {
        Node node = que.front(); que.pop();
        int dd = dist[node.r][node.c][node.t];
        int tt = (node.t + 1) % 4;
        for (int x = 0; x < 4; ++x) {
            int r = node.r + diff[x][0];
            int c = node.c + diff[x][1];
            if (!inBound(r, c)) continue;

            if (state[r][c][tt]) {
                // skip
            } else {
                if (dist[r][c][tt] < 0) {
                    dist[r][c][tt] = dd + 1;
                    que.push(Node(r, c, tt));
                    //cout << "(" << r << "," << c << ","<< tt << ")"
                    //    << " " << dd+1 << endl;
                }
            }
        }
    }
}

void solve(int tcase)
{
    const char WALL = '#';
    const char EMPTY = '.';
    const char START = 'S';
    const char GOAL = 'G';

    cin >> M >> N;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    memset(state, 0, sizeof state);
    int srow, scol;
    int trow, tcol;
    for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j) {
        if (maze[i][j] == START) {
            srow = i; scol = j;
        } else if (maze[i][j] == GOAL) {
            trow = i; tcol = j;
        } else if (maze[i][j] == WALL) {
            for (int t = 0; t < 4; ++t) state[i][j][t] = 1;
        } else {
            int turret = getTurret(maze[i][j]);
            if (turret >= 0) {
                for (int t = 0; t < 4; ++t) {
                    int dir = (turret + t) % 4;
                    int r = i, c = j;
                    do {
                        state[r][c][t] = 1;
                        r += diff[dir][0];
                        c += diff[dir][1];
                    } while (inBound(r, c) && maze[r][c] != WALL
                        && !isTurret(r,c));
                }
            }
        }
    }
    bfs(srow, scol, 0);
    int ans = -1;
    for (int t = 0; t < 4; ++t) {
        update(ans, dist[trow][tcol][t]);
    }

    cout << "Case #" << tcase << ": ";
    if (ans < 0) cout << "impossible";
    else cout << ans;
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
