// B.cpp

#include <cmath>
#include <iostream>
using namespace std;

typedef long long int64;

int main()
{
    int64 n; cin >> n;
    bool found = false;
    for (int k = 0; k <= 60; ++k) {
        // binary search an odd x such that
        // n = (x choose 2) + (2^k - 1) * x
        int64 target = 2*n;
        int64 lo = 0, hi = (int64)(sqrt(2*n)) + 3;
        //cout << lo << ' ' << hi << endl;
        while (lo + 1 < hi) {
            int64 m = (lo + hi) / 2;
            int64 x = 2*m+1; //cout << "m " << m << ' ' << x << endl;
            if (target / x < 2*((1LL<<k)-1)) { hi = m; continue; }
            if (x*(x-1) + 2*x*((1LL<<k)-1) > target) hi = m;
            else lo = m;
        }
        //cout << "k " << k << " lo " << lo << endl;
        int64 x = 2*lo + 1;
        if (x*(x-1) + 2*x*((1LL<<k)-1) == target) {
            cout << x * (1LL<<k) << endl;
            found = true;
        }
    }
    if (!found) cout << -1 << endl;
}
