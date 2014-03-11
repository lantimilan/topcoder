// sherlock-puzzle.cpp
//
// if 2*zero <= 3*one for S, then take all S * K
// else S must be deficit in one
// now we need a prefix with more ones and a suffix with more ones
// also need to know how many copies of S we can accomodate, binary search
// monotonicity: if we can accomodate m copies, we can surely accomodate m-1
// copies of S
//
// pre[i] for i = 0 to n is one - zero for S[0..i)
// post[i] for i = 0 to n is one - zero for S[i..n)
//
// what do we need?
// for each prediff = one - zero for a prefix, what is the length of
// the longest prefix
// then postdiff = deficit - prediff, and we need the length of the
// longest suffix with one - zero = postdiff

#include <cstring>
#include <iostream>
using namespace std;

const int N = 1000000;
int pre[N+5], post[N+5];  // pre[i] is the length of longest prefix with one - zero = i
                          // post[i] is the length of longest suffix with one - zero = i
char S[N+5];
int K;
int L;
int D = 1000000;

int main()
{
    scanf("%s", S);
    scanf("%d", K);
    L = strlen(S);
    int d;
    d = 0;
    for (int i = 0; i < L; ++i) {
        if (S[i] == '0') d--;
        else d++;
        pre[d+D] = i;
    }
    d = 0;
    for (int i = L-1; i >= 0; --i) {
        if (S[i] == '0') d--;
        else d++;
        post[d+D] = i;
    }
    int one, zero;
    one = zero = 0;
    for (int i = 0; i < L; ++i) {
        if (S[i] == '0') zero++;
        else one++;
    }
    if (2 * zero <= 3 * one) {
        cout << (long long)L * K << endl;
        return 0;
    }
    // opt will always have max number of complete S
    // why, prefix + suffix cannot be S, otherwise S is good already
    int lo = -1, hi = K;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        long long deficit =
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    //long long ans = lo + pre + post;  // add pre and post
    cout << ans << endl;
}
