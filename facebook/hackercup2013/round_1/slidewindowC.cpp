// slidewindowC.cpp

#include <iostream>
#include <vector>
using namespace std;

vector<int> row[40000+5];
int x[1000000+5];
int y[1000000+5];
int cnt[40000+5];
int col[40000+5];

void solve(int tcase)
{
    int W, H, P, Q, N, X, Y, a, b, c, d;
    cin >> W >> H >> P >> Q >> N >> X >> Y >> a >> b >> c >> d;

    for (int yy=0; yy<=H-Q; ++yy) row[yy].clear();
    for (int xx=0; xx<W; ++xx) col[xx] = 0;

    x[0] = X; y[0] = Y;
    row[y[0]].push_back(x[0]);
    for (int i=1; i<N; ++i) {
        x[i] = (x[i - 1] * a + y[i - 1] * b + 1) % W;
        y[i] = (x[i - 1] * c + y[i - 1] * d + 1) % H;
        row[y[i]].push_back(x[i]);
    }

    int ans = 0;
    // row[0]
    cnt[0] = 0;
    for (int yy=0; yy<Q; ++yy) {
        for (int i=0; i<row[yy].size(); ++i) {
            int xx = row[yy][i];
            col[xx]++;
            if (xx < P) cnt[0]++;
        }
    }
    for (int xx=1; xx<=W-P; ++xx) {
        cnt[xx] = cnt[xx-1] - col[xx-1] + col[xx+P-1];
    }
    for (int xx=0; xx<=W-P; ++xx) if (cnt[xx] == 0) ans++;

    // row[1] to row[last]
    for (int yy=1; yy<=H-Q; ++yy) {
        // update col and cnt
        for (int i=0; i<row[yy-1].size(); ++i) {
            int xx = row[yy-1][i];
            col[xx]--;
            if (xx < P) cnt[0]--;
        }
        for (int i=0; i<row[yy+Q-1].size(); ++i) {
            int xx = row[yy+Q-1][i];
            col[xx]++;
            if (xx < P) cnt[0]++;
        }
        for (int xx=1; xx<=W-P; ++xx) {
            cnt[xx] = cnt[xx-1] - col[xx-1] + col[xx+P-1];
        }
        for (int xx=0; xx<=W-P; ++xx) if (cnt[xx] == 0) ans++;
    }
    cout << "Case #" << tcase << ": " << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}

