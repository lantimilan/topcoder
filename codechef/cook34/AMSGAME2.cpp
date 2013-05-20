// AMSGAME2.cpp

// the desired sequence are ones with gcd = 1
//
// Let dp[pos][g] be the number of subseq from [0..pos-1]
// such that gcd = g
// basecase: dp[0][1] = 1, since an empty sequence has gcd = 1
// for pos = 0 to N-1
// for g = 1 to 10000 (max A[i])
//     g2 = gcd(g, A[pos])
//     dp[pos+1][g2] += dp[pos][g]  // use A[pos]
//     dp[pos+1][g] += dp[pos][g]  // not use A[pos]
//
// ans is dp[N][1]
//
// BELOW is WRONG
// notice that if we want all subseq with gcd for some g > 1
// then it is very easy
// the count is 2^k where k is the number of elems that div g
//

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

// you can use dp[10000] only, since dp[pos][g] depends only on dp[pos-1][]
long long dp[65][10000+5];

int gcd(int i, int j)
{
    return j == 0 ? i : gcd(j, i % j);
}

// not true
bool validate(int A[], int N, int g)
{
    int cnt = 0;
    for (int i = 0; i < N; ++i)
        cnt += (A[i] % g == 0);
    cout << "validate " << g << ' ' << dp[N][g] << ' ' << cnt << endl;
    return (dp[N][g] == (1LL<<cnt)-1);
}

void solve()
{
    int N; cin >> N;
    int A[65];
    int mx = 0;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        mx = max(mx, A[i]);
    }
    sort(A, A+N);
    //memset(dp, 0, sizeof dp);
    for (int i = 0; i <= N; ++i)
    for (int g = 0; g <= mx; ++g)
        dp[i][g] = 0;
    for (int pos = 0; pos < N; ++pos) {
        dp[pos+1][A[pos]]++;  // extend an empty subseq
        for (int g = 1; g <= A[pos]; ++g) if (dp[pos][g]) {  // extend nonempty subseq
            // the above if check saves from TLE
            int g2 = gcd(g, A[pos]);
            dp[pos+1][g2] += dp[pos][g];
            dp[pos+1][g] += dp[pos][g];
        }
    }
    for (int g = 2; g <= mx; ++g) {
        //assert(validate(A, N, g));
    }

    long long ans = dp[N][1];
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) solve();
}
