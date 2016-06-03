// kttable.cc
#include <iostream>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int A[10005];
        int B[10005];
        for (int i = 0; i < N; ++i) cin >> A[i];
        for (int i = 0; i < N; ++i) cin >> B[i];

        int ans = 0;
        int prev = 0;
        for (int i = 0; i < N; ++i) {
            int avail = A[i] - prev;
            ans += (avail >= B[i]);
            prev = A[i];
        }
        cout << ans << endl;
    }
}
