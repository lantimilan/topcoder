// two-arrays.cpp

#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

void solve()
{
    int N, K; cin >> N >> K;
    int A[1005], B[1005];
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];

    sort(A, A+N);
    sort(B, B+N, greater<int>());

    bool ans = true;
    for (int i = 0; i < N; ++i) {
        if (A[i] + B[i] < K) { ans = false; break; }
    }

    if (ans) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) solve();
}
