// prob274A.cpp

// sort, then it is always better to use a[i] instead of a[i]*k

#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

typedef long long int64;
int64 a[100000+5];
set<int64> banned;

int main()
{
    int n, k; cin >> n >> k;
    for (int i=0; i<n; ++i) cin >> a[i];
    sort(a, a+n);
    int ans = 0;
    for (int i=0; i<n; ++i) if (!banned.count(a[i])) {
        ans++; banned.insert(a[i]*k);
    }
    cout << ans << endl;
}

// Accepted
