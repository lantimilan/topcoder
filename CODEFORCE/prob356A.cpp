// prob356A.cpp
//
// use set<int> to keep track of all active knights

#include <iostream>
#include <set>
using namespace std;

set<int> knights;
int beaten[300000+5];
int n, m;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) knights.insert(i);

    for (int i = 0; i < m; ++i) {  // round
        int l, r, x; cin >> l >> r >> x;
        set<int>::iterator lit, rit, it;
        it = lit = knights.lower_bound(l);
        rit = knights.upper_bound(r);
        for (it = lit; it != rit; ) {
            beaten[*it] = x;
            set<int>::iterator it2 = it; ++it2;
            knights.erase(it);
            it = it2;
        }
        knights.insert(x);
    }
    // beaten[winner] is 0 by initialization
    for (int i = 1; i <= n; ++i) {
        if (beaten[i] == i) beaten[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << beaten[i];
    }
    cout << endl;
}
