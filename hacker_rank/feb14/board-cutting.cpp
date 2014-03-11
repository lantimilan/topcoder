// board-cutting.cpp
//
// Observation: the cut sequence is x[1..N-1] and y[1..M-1] interleaving
// within x[], must occur in decreasing order
// within y[], must occur in decreasing order
// now consider an arbitrary interleaving with x[] and y[] decreasing among
// themselves.
// if some x[j] precedes y[i], and they are adjacent, then we claim x[j] >= y[i]
// otherwise we can swap them to get a better sequence.
// what if x[j] = y[i], then it does not matter which one comes first.
// so if we have an optimal sequence, we can use this adjacent swap to
// transform into another sequence with the same cost
// this also implies that, as long as we order events/cuts with decreasing
// weight, regardless of whether they come from x[] or y[], we get an
// optimal sequence.

//
// the relative order of horizontal is irrelevant
// the relative order of vertical is irrelevant
// because each goes through only 1 segment
// but the interleaving of horizontal and vertical are important
// greedy, since each will increase segment by 1
//
// so we have to cut into 1x1 pieces, each of x[1..N] must be cut once
// and so is each of y[1..M]
// x[1..N] and y[1..M] has to be cut with decreasing weights
// now consider the last cut, is it x[N] or y[M]
// at that time all other cuts are done
// if x[N] is the last cut, the cost is x[N] * (M+1)
// if y[M] is the last cut, the cost is y[M] * (N+1)

#include <algorithm>
#include <cassert>
#include <iostream>
using namespace std;

// weight, xy
// y = 0, x = 1
pair<int, int> weights[1000000*2+5];
int x[1000000+5];
int y[1000000+5];
const int MOD = 1e9+7;

void solve()
{
    int M, N; cin >> M >> N;
    --M; --N;
    for (int i = 0; i < M; ++i) cin >> y[i];
    for (int j = 0; j < N; ++j) cin >> x[j];

    int k = 0;
    for (int i = 0; i < M; ++i) weights[k++] = make_pair(y[i], 0);
    for (int j = 0; j < N; ++j) weights[k++] = make_pair(x[j], 1);
    assert(k == M + N);
    int K = k;

    sort(weights, weights + k);
    reverse(weights, weights + k);

    int ans = 0;
    int xcnt = 1, ycnt = 1;
    for (int i = 0; i < K; ++i) {
        int val = weights[i].first;
        int axis = weights[i].second;
        //cout << val << ' ' << axis << endl;
        if (axis == 0) {  // read y
            int curr = (long long) val * xcnt % MOD;
            ans += curr; if (ans >= MOD) ans -= MOD;
            ycnt++;
        } else {  // read x
            int curr = (long long) val * ycnt % MOD;
            ans += curr; if (ans >= MOD) ans -= MOD;
            xcnt++;
        }
        //cout << ans << endl;
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
