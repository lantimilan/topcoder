// largest_sum.cpp
// Largest Sum Less Than M

#include <cassert>
#include <iostream>
using namespace std;

const int MOD = 1e9+7;
int dp[105][3005][105];  // maxid, val, kelems
int part[3005][3005];

int partition(int n)
{
    for (int i=0; i<=n; ++i)
        part[i][i] = 1;

    for (int i=1; i<=n; ++i)
    for (int j=i-1; j>=1; --j) {
        part[i][j] = part[i-j][j];
        part[i][j] += part[i][j+1];
        if (part[i][j] >= MOD) part[i][j] -= MOD;
    }
    return part[n][1];
}

int main()
{
    int n, k, M; cin >> n >> k >> M; //cout << n << ' ' << k << ' ' << M << endl;
    int d[105];
    for (int i=0; i<n; ++i) cin >> d[i];
    dp[0][0][0] = 1;
    for (int i=1; i<=n; ++i)
    for (int v=0; v<M; ++v)
    for (int c=0; c<=k; ++c)
    {
        dp[i][v][c] = dp[i-1][v][c];
        if (v - d[i-1] >= 0 && c > 0)
            dp[i][v][c] |= dp[i-1][v - d[i-1]][c-1];
    }
    int ans;
    for (ans = M-1; ans >= 0; --ans)
        if (dp[n][ans][k]) break;

    //assert(0 < ans && ans < M && M < 2000);
    cout << ans << endl;
    cout << partition(ans) << endl;
}

// Accepted

/* From discussion
* Read(N),Read(K),Read(M);

if (M==2985) // generate a SEGFAULT
{
    dyn[-1][-1][-1]=0;
    return(0);
}
if (M==2986) // generate a TLE
{
    for(;;);
}
if (M==2987) // generate a WA
{
    printf("8========================D ~~~~~~\n");
    return(0);
}

*/
