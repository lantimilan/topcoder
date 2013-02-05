// sweep line
//
// what is the problem with my implementation

#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
typedef set<int>::iterator iter_type;

const int MM = 1e6;
const int TAG = 1e9;
pii xlist[2*MM+5];
set<int> ylist;
int X[MM+5];
int Y[MM+5];

void print_set(const set<int> &st)
{
    iter_type it;
    for (it = st.begin(); it != st.end(); ++it)
        cout << *it << " ";
    cout << endl;
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
    //for (int i=0; i<N; ++i)
    //    cout << " (" << X[i] << "," << Y[i] << ") ";
    //cout << endl;
    int E=0;
    for (int i=0; i<N; ++i) {
        int l = max(0, X[i]-P+1);
        xlist[E++] = pii(l, Y[i]);
        xlist[E++] = pii(X[i], Y[i] + TAG);
    }
    sort(xlist, xlist + E);
    //pii *end = unique(xlist, xlist+E);
    //E = end - xlist;
    ylist.clear();
    int ans = (W-P+1)*(H-Q+1);
    int yall = 0;
    int pos=0, prev;
    //for (int x=0; x<=W-P; ++x) {
    for (int x=0; x<W; ++x) {
        // enter event
        while (pos < E && xlist[pos].first == x && xlist[pos].second < TAG) {
            int y = xlist[pos++].second;
            if (!ylist.count(y)) {
                pair<iter_type, bool> pp = ylist.insert(y);
                assert(pp.second);
                iter_type it = pp.first, it2;
                int upper = y, lower = max(0, y-Q+1);
                it2 = it; if (++it2 != ylist.end()) {
                    upper = min(upper, *it2 - Q);
                }
                if (it != ylist.begin()) {
                    it2 = it; --it2;
                    lower = max(lower, *it2 + 1);
                }
                //cout << "upper " << y << ' ' << upper << ' ' << lower << endl;
                if (lower <= upper) yall += upper-lower+1;
            }
        }
        //cout << "xpos " << x << ' ' << yall << endl;
        //print_set(ylist);
        ans -= yall;
        // leave event, first compute the union, then evict all exiting y[i]
        prev = pos;
        while (pos < E && xlist[pos].first == x && xlist[pos].second >= TAG) {
            int y = xlist[pos++].second - TAG;
            if (ylist.count(y)) {
                iter_type it = ylist.find(y), it2;
                int upper = y, lower = max(0, y-Q+1);
                it2 = it; if (++it2 != ylist.end()) {
                    upper = min(upper, *it2 - Q);
                }
                if (it != ylist.begin()) {
                    it2 = it; --it2;
                    lower = max(lower, *it2 + 1);
                }
                if (lower <= upper) yall -= (upper-lower+1);
            }
        }
        for (; prev < pos; ++prev) {
            int y = xlist[prev].second - TAG;
            ylist.erase(y);
        }
    }
    cout << "Case #" << tcase << ": " << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
