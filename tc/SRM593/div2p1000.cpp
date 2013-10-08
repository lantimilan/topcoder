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

const int D = 50*10000;
//vector<vector<bool> > dp(51, vector<bool>(2*D+3));
bool dp[2][4*D+3];

class MayTheBestPetWin
{
public:

int calc(vector <int> A, vector <int> B)
{
    int smin = 0, smax = 0;
    for (int i = 0; i < A.size(); ++i) {
        smin += A[i];
        smax += B[i];
    }
    int cap = smin + smax;  // offset of (max1 - max2) + (min1 - min2)
    int lim = 2*cap;  // s1 - s2 must be within [-cap, +cap]
    dp[0][cap] = true;
    for (int i = 0; i < A.size(); ++i) {
        //cout << "iter " << i << endl;
        int p1 = i&1;
        int p2 = (i+1)&1; //cout << p1 << ' ' << p2 << endl;
        memset(dp[p2], 0, sizeof(dp[p2])); //cout << "memset done" << endl;
        assert(lim <= 4*D);
        for (int d = 0; d <= lim; ++d) if (dp[p1][d]) {
            int d2;
            // use A[i],B[i] in team1
            d2 = d + B[i] + A[i]; if (0 <= d2 && d2 <= lim) { dp[p2][d2] = true; }
            // use A[i],B[i] in team2
            d2 = d - (B[i] + A[i]); if (0 <= d2 && d2 <= lim) { dp[p2][d2] = true; }
        }
    }
    int alldiff = 0;
    for (int i = 0; i < A.size(); ++i) {
        alldiff += B[i] - A[i];
    }
    cout << "dp done\n";
    int best = 2*D;
    for (int d = 0; d <= lim; ++d) {
        if (dp[A.size()&1][d]) {
            int s1, s2;
            int s = d - cap;
            s1 = (alldiff + s)/2;
            s2 = s1 - s;
            best = min(best, max(s1, s2));
        }
    }
    return best;
}
};

// TODO:
// 1. use 1-D dp to save memory
// 2. cleaner code
