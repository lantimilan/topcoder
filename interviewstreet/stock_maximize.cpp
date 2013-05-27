// stock_maximize.cpp
//
// must sell at each max
// buy on every place

#include <algorithm>
#include <iostream>
using namespace std;

int N;
int A[50000+5];

void solve()
{
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];

    long long ans = 0;
    int mx = A[N-1];
    for (int i = N-1; i >= 0; --i) {
        if (A[i] <= mx) ans += mx - A[i];
        else mx = A[i];
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}

// Accepted
