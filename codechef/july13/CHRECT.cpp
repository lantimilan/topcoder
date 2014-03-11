// CHRECT.cpp

#include <iostream>
using namespace std;

int main()
{
    int T; cin >> T;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        int ans;
        if (N * M == 2) ans = 0;
        else if (N == 1 || M == 1) ans = K;
        else ans = (K+1) / 2;
        cout << ans << endl;
    }
}
