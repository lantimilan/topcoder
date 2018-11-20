// BUDDYNIM.cc
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// If sumA > sumB, then Alice wins by picking stone one at a time.
// Bob can emulate Alice as long as two tables have the same sum, and same max.
// same sum -> Bob (emulate Alice)
// diff sum -> Alice (reomve 1 at a time)
// so for Bob to win, A[] and B[] must be identical once sorted
void solve() {
    int N, M; cin >> N >> M;
    int A[105], B[105], nA = 0, nB = 0;
    long long sumA = 0, sumB = 0;
    // only non-zero elements matters
    for (int i = 0; i < N; ++i) { cin >> A[i]; sumA += A[i]; nA += (A[i] > 0); }
    for (int i = 0; i < M; ++i) { cin >> B[i]; sumB += B[i]; nB += (B[i] > 0); }

    bool alice_win = false;
    if (sumA != sumB) alice_win = true;
    else {
        sort(A, A+N);
        sort(B, B+M);
        if (nA != nB) {
            alice_win = true;
        } else {
            for (int i = N-1, j= M-1; i >= 0 && A[i] > 0; --i, --j) {
                if (A[i] != B[j]) { alice_win = true; break; }
            }
        }
    }
    cout << (alice_win ? "Alice" : "Bob") << endl;
    /*
    vector<int> va, vb;
    for (int i = 0; i < N; ++i) {
        int k; cin >> k;
        if (k > 0) va.push_back(k);
    }
    for (int i = 0; i < M; ++i) {
        int k; cin >> k;
        if (k > 0) vb.push_back(k);
    }
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    bool bob_win = (va == vb);
    cout << (bob_win ? "Bob" : "Alice") << endl;
    */
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
