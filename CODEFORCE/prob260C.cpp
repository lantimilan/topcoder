// there can be at most one 0
// each full loop will deposit 1 into the starting box
// start is i such that r = a[i] % n and (start + r) % n = x-1
//
// init a[0..n-1]
// end  b[0..n-1]
//
// b[start] has to be min, b[start+1..x] (wrap around n)  must be at least min+1
//
// a[0..n-1]
// a[start] = b[start]*n + dist(start, x)
// a[i] set to b[i]
// all other a[i] -= b[start], for i in start+1 to x, a[i]--

#include <cassert>
#include <iostream>
using namespace std;

typedef long long int64;

const int N = 1e5;
int64 a[N+5], b[N+5];

int main()
{
    int n, x, pos, dist=0;
    int64 minval=1LL<<40;
    cin >> n >> x; --x;
    for (int i=0; i<n; ++i) cin >> b[i];
    for (int i=0; i<n; ++i) minval = min(minval, b[i]);
    pos = x;
    do {
        if (b[pos] == minval) break;
        --pos; if (pos < 0) pos += n;
        dist++;
    } while (pos != x);
    assert(dist < n);
    a[pos] = b[pos]*n + dist;
    for (int i=0; i<n; ++i) if (i != pos)
        a[i] = b[i] - b[pos];
    if (pos != x) {
        for (int i=(pos+1)%n; i != x; i=(i+1)%n)
            a[i]--;
        a[x]--;
    }
    for (int i=0; i<n; ++i) assert(a[i] >= 0);
    for (int i=0; i<n; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;

}
