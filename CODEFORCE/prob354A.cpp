// prob354A.cpp
//
// CF 206
// the DP idea would require us to use dp[i][j][2] to remember the best
// score to collect item[i..j] when prev is 0 for left or 1 for right
// this is too slow given n = 10^5
//
// observation: we only care whether an item was collected as left or right
// but those collected as left must be a prefix and those collected as right
// must be a suffix
//
// let left and right be the number of items collected as left and right
// respectively, and d1 = max(left - right -1, 0), d2 = max(right - left -1, 0)
// we will pay Ql * d1 + Qr * d2 for repeated left or right

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 100000;
int W[N+5];
int SL[N+5], SR[N+5];

int main()
{
    int n, l, r, ql, qr; cin >> n >> l >> r >> ql >> qr;
    for (int i = 0;  i < n; ++i) cin >> W[i];

    SL[0] = 0;  // SL[i] is sum W[0..i)
    for (int i = 0; i < n; ++i) SL[i+1] = SL[i] + W[i];
    SR[n] = 0;  // SR[i] is sum W[i..n)
    for (int i = n-1; i >= 0; --i) SR[i] = SR[i+1] + W[i];

    int best = 1000000000;
    for (int left = 0; left <= n; ++left) {
        int right = n - left;
        int d1, d2;
        d1 = max(0, left - right - 1);
        d2 = max(0, right - left - 1);
        int score = l * SL[left] + r * SR[n - right];
        score += d1 * ql + d2 * qr;
        best = min(best, score);
    }
    cout << best << endl;
}
