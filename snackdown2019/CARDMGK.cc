// CARDMGK.cc
#include <iostream>
using namespace std;

int A[100000+5];

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    bool good = true;
    int maxpos = 0;
    int maxval = A[0];
    int i;
    for (i = 1; i < N; ++i) {
        if (A[i] < A[i-1]) break;
        else {
            maxpos = i;
            maxval = A[i];
        }
    }
    if (i < N) {  // A[i..N) is increasing with A[N-1] <= A[0]
        for (++i; i < N; ++i) {
            if (A[i] < A[i-1]) { good = false; break; }
        }
        good = good && (A[N-1] <= A[0]);
    }
    cout << (good ? "YES" : "NO") << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
