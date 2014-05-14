// C.cpp
//
// we could have this
//
// XXXX
//X    X
// XXXX
//X  X
// XX

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

int solve2(int N, int M, int K)
{
    int ans = K;
    for (int w = 1; w <= M-2; ++w)
    for (int h = 1; h <= N-2; ++h) {
        int stone = 2*w + 2*h;
        int rem = K - (stone + w * h);
        if (rem < 0) continue;
        int cur = stone + rem;
        //cout << w << ' ' << h << ' ' << cur << endl;
        ans = min(ans, cur);
    }
    return ans;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N, M, K; cin >> N >> M >> K;
    int ans = K;
    ans = min(ans, solve2(N, M, K));
    ans = min(ans, solve2(M, N, K));
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
