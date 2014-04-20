// prob418A.cpp
//
// strategy:
// for each team i, let it beat team i+1..i+k
// do we have an issue in wrap around?
// for n teams, each with k wins, we need n * k games
// but we can have no more than (n choose 2) = n*(n-1)/2 games
// so we know n-1 >= 2*k, that is, 2*k + 1 <= n
// then the most likely wrap around case is that
// team n will beat 1, ..., k
// and team k will beat k+1, ..., 2*k
// now we need 2*k < n, which is the same as 2*k + 1 <= n
// and we have that, so it works.
//
// the only implementation detail is to use printf to do fast I/O

#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int n, k; //cin >> n >> k;
    scanf("%d%d", &n, &k);
    if (n * k > n*(n-1)/2) {
        cout << -1 << endl;
        return 0;
    }

    int m = n * k;
    //cout << m << endl;
    printf("%d\n", m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            int j2 = (i + j) % n;
            if (j2 == 0) j2 = n;
            //cout << i << ' ' << j2 << endl;
            printf("%d %d\n", i, j2);
        }
    }
}
