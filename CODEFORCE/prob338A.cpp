// prob338A.cpp

// nseg = ceiling(n / k)
// ngap = nseg
// nfill = n - ngap
// if we have one incorrect for each seg, then ans = 0
// else for the first one, we have rem = n % k
// for each next, we have 2*k
// so for m answers, ans = (m - nfill - 1) * 2k + rem

#include <iostream>
using namespace std;

const int M = 1000000000+9;

int fastpow(int a, int b)
{
    int ans = 1;
    int base = a;

    // invariant: ans * base^b = a ^ b0
    while (b) {
        if (b&1) ans = (long long) ans * base % M;
        base = (long long) base * base % M;
        b /= 2;
    }
    return ans;
}

int score_full_seg(int k, int p)
{
    int ans = fastpow(2, p) - 1;
    ans = (long long)ans * 2 % M;
    ans = (long long)ans * k % M;
    if (ans < 0) ans += M;
    return ans;
}

int main()
{
    int n, m, k; cin >> n >> m >> k;
    int ans;

    int nseg = n - m + 1;
    long long rem = (long long)(k-1) * nseg; if (m <= rem) { cout << m << endl; return 0; }
    int numk = ((m - rem) + (k-1)) / k;
    rem = m - numk * k; // cout << numk << ' ' << rem << endl;

    ans = score_full_seg(k, numk);

    ans += rem; if (ans >= M) ans -= M;
    cout << ans << endl;
}

// READ PROBLEM STATEMENT!
// a player receives 1 pt for each correct answer
// counter incr by 1 for each consecutive correct answer and reset to 0 on an incorrect answer
// when counter hit k, current score doubled and counter reset to 0
//
// find minimum score
// all doubles come early

// WA: 4 attempts, incorrectly read problem
// WA: 1 attempt, integer overflow on rem
// WA: 1 attempt, need to get ans + when doing mod
