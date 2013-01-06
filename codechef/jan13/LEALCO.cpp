// since each R[i] can be incremented at most once
// use 2^17 to record an op configuration

#include <iostream>
using namespace std;

int main()
{
    int T; cin >> T;
    int N, K, M;
    int R[20];
    int a[20];
    int ans;
    while (T--) {
        cin >> N >> K >> M;
        ans = -1;
        for (int i=0; i<N; ++i) cin >> R[i];
        for (int b=0; b<(1<<N); ++b) {
            for (int i=0; i<N; ++i) a[i] = R[i];
            for (int i=0; i<N; ++i) if (b & 1<<i) a[i]++;

            bool good = true;
            for (int i=0; i+K<=N; ++i) {
                int mx = a[i], cnt = 0;
                for (int j=0; j<K; ++j) mx = max(mx, a[i+j]);
                for (int j=0; j<K; ++j) cnt += (a[i+j] == mx);
                if (cnt >= M) { good = false; break; }
            }
            if (good) {
                int bits = 0;
                int x = b;
                while (x) { bits++; x &= x-1; }
                if (ans < 0 || ans > bits) ans = bits;
            }
        }
        cout << ans << endl;
    }
}
// Correct Answer 
// Execution Time: 0.97 