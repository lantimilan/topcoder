// project to X and Y

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int X[1000000+5];
int Y[1000000+5];
vector<pii> Xinterval;
vector<pii> Yinterval;


pii get_range(int x, int window, int cap)
{
    int xl, xr;
    xl = max(0, x-window+1); xr = min(cap, x+window);
    return pii(xl, xr);
}

void solve(int tcase)
{
    int W, H, P, Q, N, x0, y0;
    int a, b, c, d;
    cin >> W >> H >> P >> Q >> N >> x0 >> y0;
    cin >> a >> b >> c >> d;

    X[0] = x0; Y[0] = y0;
    for (int i=1; i<N; ++i) {
        X[i] = (X[i - 1] * a + Y[i - 1] * b + 1) % W;
        Y[i] = (X[i - 1] * c + Y[i - 1] * d + 1) % H;
    }
    sort(X, X+N);
    sort(Y, Y+N);

    for (int i=0; i<N; ++i) cout << X[i] << ' '; cout << endl;
    for (int i=0; i<N; ++i) cout << Y[i] << ' '; cout << endl;
    // merge interval
    Xinterval.clear(); Yinterval.clear();
    for (int i=0; i<N; ++i) {
        pii xseg = get_range(X[i], P, W-P+1);
        pii yseg = get_range(Y[i], Q, H-Q+1);
        if (!Xinterval.empty() && Xinterval.back().second >= xseg.first)
            Xinterval.back().second = xseg.second;
        else
            Xinterval.push_back(xseg);
        if (!Yinterval.empty() && Yinterval.back().second >= yseg.first)
            Yinterval.back().second = yseg.second;
        else
            Yinterval.push_back(yseg);
    }
    int xcnt=0, ycnt=0;
    for (int i=0; i<Xinterval.size(); ++i) {
        pii xseg = Xinterval[i];
        int cnt = xseg.second - xseg.first;
        xcnt += cnt;
    }
    for (int i=0; i<Yinterval.size(); ++i) {
        pii yseg = Yinterval[i];
        int cnt = yseg.second - yseg.first;
        ycnt += cnt;
    }
    int ans = W*H - xcnt*ycnt;
    ans -= ((P-1)*H + (Q-1)*W - (P-1)*(Q-1));
    cout << "Case #" << tcase << ": " << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
