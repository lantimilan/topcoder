// round1C_C.cpp
//
// Greedy, for each segment, start with mid
// Proof: suppose mid was choosen at kth step, and previous step choose a[i]
// then swap these two get the same configuration with a better score
// This proof is wrong, because a median is no longer a median after split.
//
// Solution: use dynamic programming
// dp[i][j] is the cost to remove all prisoners in [A[i]..A[j]] with the two
// endpoints excluded
// For convenience we assume A[0] and A[Q+1] at pos=0 and pos=P+1 so that
// all intervals are bounded by to-be-released prisoners.
//
// To remove a prisoner costs at most P=10^4, so total is at most 10^4 * 100
// = 10^6, int is enough.

#include <iostream>
using namespace std;

int prisoners[105];
int dp[105][105];

void chmin(int &a, int b) {
    if (b < a) a = b;
}

void solve(int tcase) {
    int P, Q; cin >> P >> Q;
    prisoners[0] = 0; prisoners[Q+1] = P+1;
    for (int i = 1; i <= Q; ++i) cin >> prisoners[i];

    // initialize, empty range has cost zero
    for (int i = 0; i <= Q; ++i) dp[i][i+1] = 0;

    for (int w = 2; w <= Q+1; ++w)
    for (int i = 0; i + w <= Q+1; ++i) {
        int j = i + w;
        int dist = prisoners[j] - prisoners[i] - 1 -1;  // k itself does not

        dp[i][j] = 1e8;
        for (int k = i+1; k < j; ++k) {
            int curr = dp[i][k] + dp[k][j] + dist;
            chmin(dp[i][j], curr);
        }
    }

    int cost = dp[0][Q+1];
    cout << "Case #" << tcase << ": ";
    cout << cost << endl;
}

int main() {
    int N; cin >> N;
    for (int t = 1; t <= N; ++t) {
        solve(t);
    }
}

