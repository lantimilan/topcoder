// This is a DP problem
// dp[i+1][j+1] = 1 if s[i..j] is a pal
// let a[i][j] be the number of pal substr in s[i..j], 1-based
// a[][] can be computed in O(n^2) time
// then query can be answered by a simple lookup

#include <cstdio>
#include <cstring>
using namespace std;

char s[5005];
int dp[5005][5005];
int a[5005][5005];

int main()
{
    scanf("%s", s);
    int n = strlen(s);
    for (int i=0; i<n; ++i)
        dp[i+1][i+1] = 1;
    for (int i=0; i+1<n; ++i)
        if (s[i] == s[i+1])
            dp[i+1][i+2] = 1;
    for (int len=3; len<=n; ++len)
        for (int i=0; i+len <=n; ++i) {
            int j = i+len-1;
            if (s[i] == s[j] && dp[i+1+1][j-1+1])
                dp[i+1][j+1] = 1;
        }

    // dp[i+1][j+1] = dp[i+1][j] + dp[i+2][j+1] - dp[i+2][j]
    for (int len=1; len<=n; ++len) {
        for (int i=0; i<n; ++i) {
            int j=i+len-1;
            a[i+1][j+1] = a[i+1][j] + a[i+2][j+1] - a[i+2][j] + dp[i+1][j+1];
        }
    }

    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", a[l][r]);
    }
}

// Accepted
