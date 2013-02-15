// count eq range and ans is prod of fact(k[i])

#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int f[200000+5];
pii a[200000+5];
int MOD;

int mult(int a, int b)
{
    return (long long)a*b % MOD;
}

int fact(int n)
{
    return f[n];
}

void init()
{
    f[0] = 1;
    for (int i=1; i<200000+5; ++i)
        f[i] = mult(f[i-1], i);
}

int main()
{
    int n; cin >> n;
    for (int i=0; i<2*n; ++i) {
        cin >> a[i].first;
        a[i].second = i >= n ? i-n : i;
    }
    cin >> MOD;
    sort(a, a+2*n);
    init();
    int ans = 1;
    for (int i=0; i<2*n; ) {
        int j=i, v=a[i].first;
        for (++j; j<2*n && a[j] == v; ++j) ;
        // multi-nomial theorem on a[i..j-1]
        // how to deal with non-prime MOD?
        ans = mult(ans, fact(j-i));
        i = j;
    }
    cout << ans << endl;
}
