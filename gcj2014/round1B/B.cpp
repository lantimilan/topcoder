// B.cpp
//
// questions:
// 1. why this work?
// 2. how many states do we have? Why this runs fast?

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct triple
{
    int A, B, K;
    triple(int a, int b, int k) {
        A = a; B = b; K = k;
    }
    bool operator<(const triple &t2) const {
        if (A != t2.A) return A < t2.A;
        if (B != t2.B) return B < t2.B;
        if (K != t2.K) return K < t2.K;
        return false;
    }
};

map<triple, long long> dp;

long long recur(int A, int B, int K)
{
    // dp cache?
    if (A < 0 || B < 0 || K < 0) return 0;
    if (A == 0 || B == 0) return max(A, B) + 1;

    triple tt(A, B, K);
    if (dp.count(tt)) return dp[tt];
    long long ans = 0;
    // after we have a pair (a,b) with len-1
    // append one bit to the end of a and b
    // use (0,0)
    ans += recur(A/2, B/2, K/2);
    // use (1,0)
    ans += recur((A-1)/2, B/2, K/2);
    // use (0,1)
    ans += recur(A/2, (B-1)/2, K/2);
    // use (1,1)
    if (K > 0)
        ans += recur((A-1)/2, (B-1)/2, (K-1)/2);
    //cout << A << ' ' << B << ' ' << K << ' ' << ans << endl;
    return dp[tt] = ans;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int A, B, K; cin >> A >> B >> K;
    --A; --B; --K;

    long long ans = recur(A, B, K);
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
