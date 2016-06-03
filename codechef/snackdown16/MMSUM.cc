// MMSUM.cc
// Given an array of int, size 10^5
// find max subarray sum, with zero or one element reomved
//
// if all elem >= 0, then ans is the sum of the array
// a prefix is useful if its sum >= 0,
// it is not useful if its sum < 0
//
// last[i] is the sum ending at pos[i]
// first[i] is the sum starting at pos[i]
//
// last[0] = A[0]
// first[N-1] = A[N-1]
// last[i] = max(A[i], last[i-1] + A[i])
// first[i] = max(A[i], first[i+1] + A[i])

#include <algorithm>
#include <iostream>
using namespace std;

const int X = 100000;
long long A[X+5];
long long first[X+5];
long long last[X+5];

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0; i < N; ++i) cin >> A[i];

        last[0] = A[0];
        for (int i = 1; i < N; ++i) last[i] = max(A[i], last[i-1] + A[i]);
        first[N-1] = A[N-1];
        for (int i = N-2; i >= 0; --i) first[i] = max(A[i], first[i+1] + A[i]);

        long long ans = A[0];
        for (int i = 0; i < N; ++i) {
            ans = max(ans, last[i]);
            if (i+2 < N) {
                ans = max(ans, last[i] + first[i+2]);
            }
        }
        cout << ans << endl;
    }
}
