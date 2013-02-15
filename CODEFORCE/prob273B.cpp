// count eq range and ans is prod of fact(k[i])
// divided by 2^(sum of num[i] such that a[i]==b[i])

// things to watch:
// 1. fact takes at most n = 10^5
// 2. every pow index incr by 1 implies fact(k) becomes fact(k+2)
// an extra pair have equal first coordinate

#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;


int a[100000+5];
int b[100000+5];
int c[200000+5];
int MOD;

int mult(int a, int b)
{
    return (long long)a*b % MOD;
}

int fact(int n, int &two)
{
    int ans=1;
    for (int i=2; i<=n; ++i) {
        int t = i;
        if (two > 0 && t % 2 == 0) { t /= 2; two--; }
        ans = (long long)ans * t % MOD;
    }
    return ans;
}

int main()
{
    int n; cin >> n;
    int two = 0;
    for (int i=0; i<n; ++i) { cin >> a[i]; c[i] = a[i]; }
    for (int i=0; i<n; ++i) {
        cin >> b[i]; c[i+n] = b[i];
        two += (a[i] == b[i]);
    }
    cin >> MOD;
    sort(c, c+2*n);
    int ans = 1;
    for (int i=0; i<2*n; ) {
        int j=i, v=c[i];
        for (++j; j<2*n && c[j] == v; ++j) ;
        ans = mult(ans, fact(j-i, two));
        i = j;
    }
    assert(two == 0);
    cout << ans << endl;
}
