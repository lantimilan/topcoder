// prob459B.cpp

#include <algorithm>
#include <iostream>
using namespace std;

int b[200000 + 5];
int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    sort(b, b+n);
    long long ans = 0;
    int bmin = b[0], bmax = b[n-1];
    if (bmin == bmax) {
        ans = (long long)n * (n-1) / 2;
    } else {
        int c1, c2;
        int i;
        for (i = 0; i < n && b[i] == bmin; ++i) ;
        c1 = i;
        for (i = n-1; i >= 0 && b[i] == bmax; --i) ;
        c2 = n-1 - i;
        ans = (long long)c1 * c2;
    }
    cout << bmax - bmin << ' ' << ans << endl;
}

