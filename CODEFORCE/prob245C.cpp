#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

const int INF = 1000000;
int coins[105];
pii dp[105][1005];

pii calc(int pos, int n)
{
    //cout << "calc " << pos << ' ' << val << endl;
    int l, r, op, rem, lop, rop, lval, rval, val;
    l = 2*pos+1;
    r = 2*pos+2;
    val = coins[pos];

    if (l >= n) return pii(val, 0);  // leaf, no op can be done

    if (dp[pos][val].first >= 0) return dp[pos][val];

    lop = rop = lval = rval = 0;
    pii p;
    p = calc(l, n);
    lval = p.first; lop = p.second;
    if (r < n) {
        p = calc(r, n);
        rval = p.first; rop = p.second;
    } else {  // only left subtree, dead if root is nonzero
        if (val > 0) return pii(val, INF);
    }
    if (lop >= INF || rop >= INF) { op = INF; }
    else { op = lop + rop + max(lval, rval); }
    rem = max(0, val - max(lval, rval));
    return dp[pos][val] = pii(rem, op);
}

int main()
{
    int ans = 0;
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> coins[i];
    }

    if (n < 3) {  // since all a[i] >=1, this case is -1
        cout << -1 << endl;
        return 0;
    }

    // notice (i, 2*i+1, 2*i+2) is heap structure
    memset(dp, -1, sizeof dp);
    pii p = calc(0, n);
    ans = p.second;
    ans += p.first;
    if (ans >= INF) cout << -1 << endl;
    else cout << ans << endl;
}

// Accepted
