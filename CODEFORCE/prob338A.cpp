// prob338A.cpp

// the problem:
// each correct answer receives 1 pt
// also cnt with consecutive correct answers
// score double once cnt hits k, then cnt reset
//
// to minimize total score, we use the incorrect to separate correct into
// segments, to limit the double score effect, we want all double to come
// as early as possible
// so the first segment has rem, and the other segments each has k-1 correct
// another way to arrange this is to have all segments with k-1, then
// distribute rem correct into segments, it is easy to see the best
// is to add all to first segment
//
// we want to minimize doubles, so we minimize both the number of times we
// double, and the actual value we double

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

// k -> 2k
// 2k + k = 3k -> 6k
// 6k + k = 7k -> 14k
// s[0] = 0
// s[1] = 2k = s[0] + 2k
// s[2] = 6k = s[1] + 4k
// s[3] = 14k = s[2] + 8k
// ...
// s[i] = s[i-1] + 2^i*k
// so, s[i] = 2k + 4k + 8k + ... + 2^i*k = 2k* (2^i - 1)
int score_full_seg(int k, int p)
{
    int ans = fastpow(2, p) - 1;
    ans = (long long)ans * 2 % M;
    ans = (long long)ans * k % M;  // now -M < ans < M
    if (ans < 0) ans += M;
    return ans;
}

int main()
{
    int n, m, k; cin >> n >> m >> k;
    int ans = m;  // we always have m points for m correct answers

    int nseg = n - m + 1;  // incorrect is n-m
    long long other = (long long)(k-1) * nseg;
    // if we can spread with all segs having k-1 or less
    // we only get m points
    if (other >= m) { cout << ans << endl; return 0; }
    other -= (k-1);  // other is now the (nseg-1) segs with k-1 each
    int numk = (m - other) / k;  // number of full size=k blocks we have

    ans = score_full_seg(k, numk);
    ans += m - numk * k;
    if (ans >= M) ans -= M;
    cout << ans << endl;
}
// Accepted

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
