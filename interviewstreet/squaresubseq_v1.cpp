// square subseq
//
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000000+7;

char s[205];
int dp[105][205][205];
int sum[105][205][205];

inline int add(int a, int b)
{
    return ((long long)a+b) %MOD;
}
inline int sub(int a, int b)
{
    return ((long long)a-b+MOD)%MOD;
}

void refadd(int &a, int b)
{
    a = ((long long)a+b)%MOD;
}

void solve(int tcase)
{
    gets(s); //puts(s);
    memset(dp, 0, sizeof dp);
    memset(sum, 0, sizeof sum);
    int n = strlen(s);
    int ans=0;

    for(int left=1; left<n; ++left)
    for(int right=left+1; right<=n; ++right)
        if (s[left-1]==s[right-1]) {
            dp[1][left][right]=1;
            refadd(ans, dp[1][left][right]);
        }

    for(int len=2; len<=n/2; ++len)
    {
        int ll=len-1;
        for(int left=1; left<=n; ++left)
        for(int right=1; right<=n; ++right)
        {
            sum[ll][left][right]=dp[ll][left][right];
        }
        for(int left=1; left<=n; ++left)
        for(int right=1; right<=n; ++right)
        {
            refadd(sum[ll][left][right], sum[ll][left-1][right]);
        }
        for(int left=1; left<=n; ++left)
        for(int right=1; right<=n; ++right)
        {
            refadd(sum[ll][left][right], sum[ll][left][right-1]);
        }
        for(int left=1; left<n; ++left)
        for(int right=left+1; right<=n; ++right)
            if (s[left-1]==s[right-1])
            {
                for(int l=1; l<left; ++l)
                for(int r=left+1; r<right; ++r)
                refadd(dp[len][left][right], dp[len-1][l][r]);
                //int t = sub(sum[len-1][left-1][right-1], sum[len-1][left-1][left]);
                //refadd(dp[len][left][right], t);
                refadd(ans, dp[len][left][right]);
            }
        for(int left=1; left<n; ++left)
        for(int right=left+1; right<=n; ++right) if (dp[len][left][right])
        {
            printf("len %d left %d right %d dp %d\n", len, left, right, dp[len][left][right]);
        }
        printf("len %d, ans %d\n", len, ans);
    }

//    int ans=0;
//    for(int len=1; len<=n/2; ++len) {
//    for(int left=1; left<n; ++left)
//    for(int right=left+1; right<=n; ++right)
//        refadd(ans, dp[len][left][right]);
//    }

    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=1; t<=T; ++t)
        solve(t);
}
