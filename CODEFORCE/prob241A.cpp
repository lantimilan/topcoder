// observation
// you move to the first place with max s[i]
// then stay to get enough fuel to reach city c[n-1], assume start c[0]

// the move is from c[0] to c[1] to c[2] ... c[n-1]
// each move to next city results in an instant refuel of s[i]
// if not enough to reach c[i+1], refuel at the best place so far,
// which is mx
#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <utility>
using namespace std;

int d[1005];
int main()
{
    int m, k; scanf("%d%d", &m, &k);
    for(int i=0; i<m; ++i) scanf("%d", d+i);
    int fuel = 0, ans = 0;
    int mx = 0;
    for(int i=0; i<m; ++i) {
        int s; scanf("%d", &s);
        if (s > mx) mx = s;  // supply at mx so far
        fuel += s;  // immediate get s after one hop
        while (fuel < d[i]) {
            fuel += mx; // refuel at mx
            ans += k;
        }
        ans += d[i];
        fuel -= d[i];
    }
    printf("%d\n", ans);
}
// Accepted
