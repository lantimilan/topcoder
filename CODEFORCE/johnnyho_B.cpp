#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <complex>
using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef stringstream ss;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define clr(t, v) memset((t), (v), sizeof(t))
#define w(a) #a << ": " << (a) << "  "

#define rep(i, n) for (int i = 0, _##i = (n); i < _##i; ++i)
#define dwn(i, n) for (int i = (n); --i >= 0;)
#define repr(i, l, r) for (int i = (l), _##i = (r); i < _##i; ++i)
#define dwnr(i, l, r) for (int i = (r), _##i = (l); --i >= _##i;)
#define repi(i, a) for (__typeof((a).begin()) i = (a).begin(), _##i=(a).end(); i != _##i; ++i)
#define dwni(i, a) for (__typeof((a).rbegin()) i = (a).rbegin(), _##i=(a).rend(); i != _##i; ++i)

bool islucky(int a) {
    return a == 4 || a == 7;
}

string s;
int dp[11][11][2];
int cnt(int numdigs, int ind, bool isl) {
    if (numdigs < 0) return 0;
    if (ind == s.size()) return numdigs == 0;
    int &res = dp[numdigs][ind][isl];
    if (~res) return res;
    res = 0;
    if (isl) {
        rep (i, 10) {
            res += cnt(numdigs - islucky(i), ind + 1, true);
        }
    } else {
        rep (i, s[ind] - '0' + 1) {
            res += cnt(numdigs - islucky(i), ind + 1, i != (s[ind] - '0'));
        }
    }
    return res;
}

const int md = 1000000007;
int arr[11];

int dfs(int a, int lim) {
    if (lim < 0) return false;
    if (a == 0) return 1;
    int ans = 0;
    rep (i, 11) {
        if (arr[i] == 0) continue;
        int t = arr[i];
        arr[i]--;
        ans += ll(dfs(a - 1, lim - i)) * t % md;
        ans %= md;
        arr[i]++;
    }
    return ans;
}

int main() {
//  freopen("a.in", "r", stdin); freopen("a.out", "w", stdout);
    cout << fixed << setprecision(12);
    
    clr(dp, -1);
    
    cin >> s;
    int finans = 0;
    rep (i, 11) {
        int t = cnt(i, 0, 0);
        if (i == 0) t--;
        finans += ll(dfs(6, i - 1)) * t % md;
        finans %= md;
        arr[i] = t;
    }
    cout << finans << endl;
}
