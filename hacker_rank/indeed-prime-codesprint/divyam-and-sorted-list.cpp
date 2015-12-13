// divyam-and-sorted-list.cpp
#include <iostream>
using namespace std;

const int M = 1e5;
long long A[M+5];
long long B[M+5];
long long C[M+5];

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];

    bool found = true;
    C[0] = min(A[0], B[0]);
    for (int i = 1; i < N; ++i) {
        long long prev = C[i-1];
        if (A[i] < prev && B[i] < prev) {
            found = false;
            break;
        } else if (A[i] < prev) {
            C[i] = B[i];
        } else if (B[i] < prev) {
            C[i] = A[i];
        } else {
            C[i] = min(A[i], B[i]);
        }
    }
    cout << (found ? "YES" : "NO") << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

