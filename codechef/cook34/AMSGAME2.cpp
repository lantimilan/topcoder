// AMSGAME2.cpp

// the desired sequence are ones with gcd = 1
//
// let p1, p2, ..., p[k] be all primes that divides some A[pos]
// then ans = 2^N - 1 - number of subseq that divsides some p[i]
// the 1 is for empty subseq
//
// to count the set of union of subseq[p] for some prime p
// inclusion exclusion
//
// for each pos = 0 to N-1
// we use A[pos] to update the count of subseq[d] where d is
// the product of some prime factors of A[pos]
//
// for each d that is a product of distinct primes and also a divisor
// of A[pos], we can extend every subseq for d with or without A[pos],
// including empty subseq, so the count for d is increased by 1LL<<cnt[d]
//
// note that the count of subseq with gcd divides d is 2^cnt[d] since
// each A[i] that divides d can either be picked or skipped
//
// One thing to notice is that MAXN is only 10^4 so each A[pos] has at most 5
// distinct primes, because 2 * 3 * 5 * 7 * 11 * 13 > 10^4
//

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10000;
int cnt[MAXN+5];
int isprime[MAXN+5];
int divs[MAXN+5];
int square[MAXN+5];

void init()
{
    for (int i = 0; i <= MAXN; ++i) square[i] = 0;
    for (int i = 2; i <= MAXN; ++i) isprime[i] = 1;
    for (int i = 2; i <= MAXN; ++i) if (isprime[i]) {
        divs[i] = i;
        for (int j = i*i; j <= MAXN; j += i) {
            isprime[j] = 0;
            divs[j] = i;
            if (j % (i*i) == 0) square[j] = 1;
        }
    }
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
    for (int d = 0; d <= mx; ++d) {
        cnt[d] = 0;
    }

    long long ans = 1LL << N;
    for (int i = 0; i < N; ++i) {
        int val = A[i];
        vector<int> fact;
        while (val > 1) {
            int d = divs[val];
            fact.push_back(d);
            while (val % d == 0) val /= d;
        }
        int m = fact.size();
        for (int b = 1; b < (1<<m); ++b) {
            int bits = 0;
            int mask = b;
            while (mask) {
                bits++;
                mask &= mask-1;
            }
            int val = 1;
            for (int j = 0; j < m; ++j) if (b & 1<<j)
                val *= fact[j];
            long long incr = 1LL << cnt[val];  // every subseq that divides val, including empty subseq
            if (bits & 1) {
                ans -= incr;
            } else {
                ans += incr;
            }
            cnt[val]++;
        }
    }
    cout << ans-1 << endl;  // subtract empty subseq
}

int main()
{
    init();
    int T; cin >> T;
    while (T--) solve();
}
