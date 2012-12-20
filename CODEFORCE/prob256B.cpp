// from uwi's solution
// binary search
// area calculation: 4 spines and 4 triangles
//
// Accepted
///////////////////////////////////////////////////
#include <iostream>
using namespace std;

typedef long long int64;

int64 hor(int64 t, int64 k)
{
    return min(t, k);
}

int64 diag(int64 t, int64 xlen, int64 ylen)
{
    int64 ans, xrem, yrem;
    if (t >= xlen + ylen) return xlen * ylen;
    ans = t*(t+1)/2;
    xrem = t - xlen;
    yrem = t - ylen;
    if (xrem > 0) ans -= xrem * (1+xrem) /2;
    if (yrem > 0) ans -= yrem * (1+yrem) /2;
    return ans;
}

bool check(int64 n, int64 x, int64 y, int64 t, int64 c)
{
    int64 sum = 1;
    sum += hor(t, x-1);
    sum += hor(t, y-1);
    sum += hor(t, n-x);
    sum += hor(t, n-y);
    //cout << sum << ' ';
    sum += diag(t-1, x-1, y-1);
    sum += diag(t-1, x-1, n-y);
    sum += diag(t-1, n-x, y-1);
    sum += diag(t-1, n-x, n-y);
    //cout << sum << ' ';
    //cout << endl;
    return sum >= c;
}

int main()
{
    int n, x, y, c; cin >> n >> x >> y >> c;
    int lo=-1, hi=2*n;
    while (lo+1 < hi) {
        int mid = (lo+hi)/2;
        if (check(n, x, y, mid, c)) hi = mid;
        else lo = mid;
    }
    cout << hi << endl;
}
