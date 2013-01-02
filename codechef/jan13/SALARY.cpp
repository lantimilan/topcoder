
// Observation:
// look at the max, say there are k max, then every k rounds will incr
// each max by k-1, and others by k
//
// Claim: there exists some a[i] such that exempt[i]=0
// Proof: Suppose for contradiction that all a[i] have exempt[i] > 0
// then we can decrease all exempt[i] by 1 and still this exempt[] array
// is feasible
//
// Claim: All a[i] with exempt[i]=0 is min among all a[0..n-1]
// Proof: Suppose not, then some a[i] with exempt[i]=0 and a[i] is not min.
// now consider some j such that a[j] is min, and exempt[j] >= 0. We have
// a[i] > a[j], after k rounds, a[i] is incremented by k and a[j] is incremented// by no more than k, so b[i] = a[i] + k > a[j] + k >= b[j].
// but this contradicts with the fact that b[i] = b[j] since all final values
// must be equal.
//
// Now the algorithm:
// Binary search for target
// number of rounds k = target - a[min]
// then we calculate sum of the exemptions
// if sum = k, then done
// else if sum < k, then we need fewer rounds as we can decrease all final
// values by some amount
// else sum > k,

#include <algorithm>
#include <iostream>
using namespace std;

void solve()
{
    int N; cin >> N;
    int W[105];
    for (int i=0; i<N; ++i) cin >> W[i];
    sort(W, W+N);

    int ans = 0;
    while (true) {
        int p;
        for (p=N-1; p>=0; --p)
            if (W[p] != W[N-1])
                break;
        if (p<0) break;
        int k = N-1 - p;
        int d = W[p+1] - W[p];
        for (int i=0; i<=p; ++i)
            W[i] += k*d;
        for (int i=p+1; i<N; ++i)
            W[i] += (k-1)*d;
        ans += k*d;
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}
// Accepted