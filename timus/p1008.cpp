// simulation

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;
int matrix[15][15];
int pre[15][15];
int post[15][15];
int X[105], Y[105];

bool inbound(int x, int y)
{
    return 1<=x && x<=10 && 1<=y && y<=10;
}

int main()
{
    string line;
    getline(cin, line);
    bool space = false;
    for (int i=0; i<line.length(); ++i)
        if (line[i] == ' ') { space = true; break; }

    int d[][2] = {{+1,0}, {0,+1}, {-1,0}, {0,-1}, };
    char dir[] = "RTLB";
    if (space) {  // RTLB representation
        int sx, sy; sx = sy = 0;
        int i;
        for (i=0; i<line.length(); ++i) {
            if (line[i] == ' ') break;
            sx = sx*10 + line[i]-'0';
        }
        for (++i; i<line.length(); ++i) {
            sy = sy*10 + line[i] - '0';
        }
        vector<pii> ans;
        memset(pre, 0, sizeof pre);
        queue<pii> que; que.push(pii(sx,sy)); pre[sx][sy] = 1;
        while (!que.empty()) {
            pii p = que.front(); que.pop();
            ans.push_back(p);
            sx = p.first; sy = p.second;
            getline(cin, line);
            for (int i=0; line[i] != ',' && line[i] != '.'; ++i) {
                int x;
                for (x=0; x<4; ++x) if (line[i] == dir[x]) break;
                if (x < 4) {
                    int x2, y2;
                    x2 = sx + d[x][0]; y2 = sy + d[x][1];
                    que.push(pii(x2,y2)); pre[x2][y2] = 1;
                }
            }
        }
        sort(ans.begin(), ans.end());
        cout << ans.size() << endl;
        for (int i=0; i<ans.size(); ++i)
            cout << ans[i].first << ' ' << ans[i].second << endl;
    } else {  // pair reprentation
        int n = 0;
        for (int i=0; i<line.length(); ++i) {
            n = 10*n + line[i] - '0';
        }
        memset(matrix, 0, sizeof matrix);
        int sx, sy; sx = sy = 20;
        for (int i=0; i<n; ++i) {
            cin >> X[i] >> Y[i];
            matrix[X[i]][Y[i]] = 1;
            if (X[i] < sx || X[i] == sx && Y[i] < sy) {
                sx = X[i]; sy = Y[i];
            }
        }
        cout << sx << ' ' << sy << endl;
        memset(pre, 0, sizeof pre);
        memset(post, 0, sizeof post);
        queue<pii> que;
        que.push(pii(sx,sy)); pre[sx][sy] = 1;
        for (int i=0; i<n; ++i) {
            pii p = que.front(); que.pop();
            sx = p.first; sy = p.second; post[sx][sy] = 1;
            int d[][2] = {{+1,0}, {0,+1}, {-1,0}, {0,-1}, };
            char row[5] = {0}; int rowcnt = 0;
            for (int t=0; t<4; ++t) {
                int x, y;
                x = sx + d[t][0];
                y = sy + d[t][1];
                if (inbound(x,y) && matrix[x][y] && !pre[x][y]) {
                    row[rowcnt++] = dir[t];
                    if (!pre[x][y]) { que.push(pii(x,y)); pre[x][y] = 1; }
                }
            }
            cout << row;
            if (i==n-1) cout << ".\n";
            else cout << ",\n";
        }
    }
}

// 4731124  05:03:11 21 Jan 2013
// lantimilan  1008. Image Encoding    C++ Accepted    0.015   216 KB
