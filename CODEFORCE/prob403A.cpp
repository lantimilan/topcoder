// prob403A.cpp
//
// recursive,
// if we can build a graph for n-1 vertices, we can build one for n vertices
// proof: adding nth vertex cannot violate the 2k+p subgraph constraint
// WRONG, because even if there is a graph for 2n+p, there might not be a graph
// for 2(n-1) + p
//
// n=5 is complete graph
//
// why constraint 5 <= n <= 24
// n >= 5 because for n under 5, we have n(n-1)/2 < 2n
// n <= 24 because the judge need to check all subgraph and there are 2^n such
// subgraph

#include <cassert>
#include <iostream>
using namespace std;

void solve()
{
    int n, p; cin >> n >> p;

    int edge = 2 * n + p;

    for (int d = 1; d < n; ++d)
    for (int i = 1; i <= n; ++i)
    if (edge > 0)
    {
        int j = (i + d) % n;
        if (j == 0) j = n;
        cout << i << ' ' << j << endl;
        edge--;
    }
    assert(edge == 0);
}

int main()
{
    int t; cin >> t;
    for (int x = 0; x < t; ++x) {
        solve();
    }
}
