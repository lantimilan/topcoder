// QUEUE2.cc
#include <algorithm>
#include <iostream>
using namespace std;

int A[100000+5];

void solve() {
    int N, M, K, L; cin >> N >> M >> K >> L;
    for (int i = 0; i < N; ++i) cin >> A[i];
    A[N++] = K;
    sort(A, A+N);
    long long waittime = -1;
    int pos = -1;
    for (int i = 0; i < N; ++i) {
        int done = A[i] / L;
        int num = M - done + i;
        long long t = 1LL * (num+1) * L - A[i] % L;
        if (waittime < 0 || waittime > t) {
            waittime = t;
            pos = i;
        }
    }
    // cerr << "pos=" << A[pos] << endl;
    cout << waittime << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
