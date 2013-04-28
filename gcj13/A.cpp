// binary search

#include <cmath>
#include <iostream>
using namespace std;

typedef long long int64;

void solve(int tcase)
{
    int64 r, t; cin >> r >> t;
    int64 lo, hi;
    lo = 0; hi = (int64)sqrt(t)+1;
    while (lo + 1 < hi) {
        int64 k = lo + (hi - lo) / 2;
        if ((2*r + 1) <= t / (k+1) - 2*k) lo = k;
        else hi = k;
    }
    cout << "Case #" << tcase << ": ";
    cout << lo+1 << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
