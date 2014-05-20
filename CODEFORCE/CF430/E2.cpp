/**************************************************
 *        Problem:  Codeforces #245 Div.2 Problem E
 *         Author:  clavichord93
 *          State:
 **************************************************/

/**************************************************
 * Header
 **************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <climits>
#include <cassert>
#include <cmath>
#include <string>
#include <bitset>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <utility>
#include <numeric>
#include <limits>
#define Fill(a, b) memset(a, b, sizeof(a))
#define Copy(a, b) memcpy(a, b, sizeof(b))
#define NPOS string::npos
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define erep(j, a) for (Edge *j = a; j; j = j->next)
#define irep(i, a) for (__typeof(a.begin()) i = a.begin(); i != a.end(); i++)
#define srep(sub, s) for (int sub = s & (s - 1); sub; sub = (sub - 1) & s)
#define sqr(a) ((a) * (a))
#define R(x) scanf("%d", &x)
#define SS(a, b) scanf("%d %d", &a, &b)
#define SSS(a, b, c) scanf("%d %d %d", &a, &b, &c)
#define O(x) pf("%d\n", x)
#define TEST int T;scanf("%d", &T);for (int cas = 1; cas <= T; cas++)
#define sf scanf
#define pf printf
#define pb push_back
#define ppb pop_back
#define pft push_front
#define ppf pop_front
#define mp make_pair
#define vec vector
#define it iterator
#define fir first
#define sec second
#define x first
#define y second
#define all(a) a.begin(),a.end()
#define sz(a) (int)(a.size())
#define bg(a) (a).begin()
#define en(a) (a).end()
#define clr(a) (a).clear()
#define dbg(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl
#define bit_cnt(x) __builtin_popcount((unsigned)x)
#define gcd(a, b) __gcd(a, b)
#define sqr(a) ((a) * (a))
#define lch(t) (t << 1)
#define rch(t) (t << 1 | 1)
#define inf numeric_limits<int>::max()
#define finf numeric_limits<double>::infinity()
using namespace std;
template<class T> inline bool gmin(T &a, T b) { if (a > b) return a = b, true; return false; }
template<class T> inline bool gmax(T &a, T b) { if (a < b) return a = b, true; return false; }
template<class T> T exgcd(T a, T b, T &x, T &y) { if (!b) return x = (T)1, y = (T)0, a; else { T d = exgcd(b, a % b, y, x); return y -= a / b * x, d; } }
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<double, double> pdd;
typedef pair<double, pdd> pddd;
typedef vec<int> vi;
typedef vec<double> vd;
typedef vec<pii> vii;
typedef vec<pdd> vdd;
typedef istringstream iss;
typedef ostringstream oss;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const double DINF = 1e10;
const double EPS = 1e-9;
const double PI = 3.14159265358979323846264338327950288;
const double TAU = 2.0 * PI;
inline int sgn(const double &a) { return a > EPS ? 1 : (a < -EPS ? -1 : 0); }
inline int lowbit(int i) { return i & (-i); }
struct Initializer { Initializer() { ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); } } initializer;

/**************************************************
 * Templates
 **************************************************/



/**************************************************
 * Main
 **************************************************/

const int MAXN = 30;

int n, top;
int size[MAXN], cnt[MAXN], c[MAXN];
bool ans;

void dfs1(int);

void dfs2(int cur, int now, int rest, int tot) {
    if (rest == 0) {
        if (tot < 2) return;
        if (size[top] == c[cur]) cnt[top]++;
        else ++top, size[top] = c[cur], cnt[top] = 1;
        dfs1(cur + 1);
    }
    else {
        if (now > top) return;
        if (size[now] > rest) return;
        for (int i = now; i <= top; i++) {
            for (int j = 1; j <= cnt[i] && j * size[i] <= rest; j++) {
                cnt[i] -= j;
                dfs2(cur, i + 1, rest - j * size[i], tot + j);
                if (ans) return;
                cnt[i] += j;
            }
        }
    }
}

void dfs1(int i) {
    if (i > n) {
        ans = 1;
        return;
    }
//    pf("dfs %d:\n", c[i]);
//    rep (j, 1, top) pf("%d %d\n", size[j], cnt[j]);
    dfs2(i, 1, c[i] - 1, 0);
}

int main() {
    R(n);
    rep (i, 1, n) R(c[i]);
    sort(c + 1, c + 1 + n);
    if (c[n] != n) pf("NO\n");
    else {
        int st = 1;
        top = 1;
        size[1] = 1;
        cnt[1] = 0;
        while (c[st] == 1) st++, cnt[1]++;
        ans = 0;
        dfs1(st);
        if (ans) pf("YES\n");
        else pf("NO\n");
    }

    return 0;
}
