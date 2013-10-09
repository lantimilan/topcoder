#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;



// two ways to define a state
// 1. bitmask of 2^k, this gives 2^50 states to partition 50 elements, too much
// 2. (smin, smax) pairs, this defines a state of a partition because we know
// smin for all elements and smax for all elements, so we can get the other pair
// for the same partition
// unfortunately this is still too many, because smin and smax could be as large
// as 50*10000 = 5*10^5, so the total number of states could be 25 * 10^10
//
// fortunately there is a way to get around the state explosion
// notice that the two scores for a partition, be s1 and s2
// s1 = max1 - min2
// s2 = max2 - min1
// we know s1 + s2 = smax - smin
// if we also know s1 - s2 = (max1 - max2) + (min1 - min2), then we know s1 and s2
// therefore s1 - s2 is the state that we keep for a prefix of element[0..i-1]
//
// each item i must be either in team1 or team2
// suppose we have computed s1 - s2 for prefix of element[0..i-1], and we are
// processing A[i],B[i],
//
// 1. put A[i],B[i] in team1, we get
// s1 - s2 += B[i] + A[i]
// 2. put A[i],B[i] in team2, we get
// s1 - s2 += -(B[i] + A[i])
//
// base case is dp[0][0] = true
//
// once done, we run s = -smax-smin to smax+smin, and for each valid s,
// we compute the two scores
// s1 + s2 = smax - smin
// s1 - s2 = s
//
// we update best with max(s1, s2)

// alternative DP
// let dp[i][s] be true if A[0..i-1] can form a partition with score s,
// that is, for the partition, max1 - min2 >= max2 - min1
//
// base cae dp[0][0] = true
// after we computed dp[i][s] for all possible s for A[0..i-1]
// for each valid s,
// we could add A[i] to either team max or team min
// for team max, t1 = s + B[i], and t1 is a valid score for A[0..i]
// for team min, s1 = s, s2 = smax - smin - s1
// t1 = s1 - A[i], t2 = s2 + B[i]
// we have max(t1, t2) as a valid score for A[0..i]
// in other words, we have just extended a configuration for A[0..i-1]
// to A[0..i] by adding A[i]
//
// score can be as low as -smin, and as high as +smax

const int D = 50*10000;
bool dp[2][2*D+3];

class MayTheBestPetWin
{
public:

int calc(vector <int> A, vector <int> B)
{
    int smin[55], smax[55];
    smin[0] = smax[0] = 0;
    for (int i = 0; i < A.size(); ++i) {
        smin[i+1] = smin[i] + A[i];
        smax[i+1] = smax[i] + B[i];
    }
    int N = A.size();
    int cap = smin[N] + smax[N];
    int diff = smin[N];
    dp[0][diff] = true;
    for (int i = 0; i < A.size(); ++i) {
        //cout << "iter " << i << endl;
        int p1 = i&1;
        int p2 = (i+1)&1; //cout << p1 << ' ' << p2 << endl;
        memset(dp[p2], 0, sizeof(dp[p2])); //cout << "memset done" << endl;
        for (int d = 0; d <= cap; ++d) if (dp[p1][d]) {
            int s1, s2, t1, t2;
            s1 = d - diff; s2 = smax[i] - smin[i] - s1;
            // use A[i], B[i] in team max
            t1 = s1 + B[i]; t2 = s2 - A[i];
            t1 = (abs(t1) >= abs(t2)) ? t1 : t2;
            t1 += diff;
            assert(0 <= t1 && t1 <= cap);
            dp[p2][t1] = true;
            // use A[i],B[i] in team min
            t1 = s1 - A[i]; t2 = s2 + B[i];
            t1 = (abs(t1) >= abs(t2)) ? t1 : t2;
            t1 += diff;
            assert(0 <= t1 && t1 <= cap);
            dp[p2][t1] = true;
        }
    }
    int best = 2*D;
    for (int d = 0; d <= cap; ++d) {
        if (dp[A.size()&1][d]) {
            best = min(best, abs(d - diff));
        }
    }
    return best;
}
};

// TODO:
// 1. use 1-D dp to save memory
// 2. cleaner code
