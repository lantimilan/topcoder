// sort by finish time
// dp[0] = 0
// dp[t] = max(dp[t-1], 
//             for each job i with finish[i] = t
//             dp[start[i]] + C[i]
//
#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

pii jobs[2005];
int dp[50];
int C[2005];

void solve()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d%d%d", &jobs[i].second, &jobs[i].first, C+i);
    }
    dp[0] = 0;
    int last = 48;
    for(int t=1; t<=last; ++t) {
        dp[t] = dp[t-1];
        for(int i=0; i<N; ++i) {
            if (jobs[i].first == t) {
                int curr = dp[jobs[i].second] + C[i];
                dp[t] = max(dp[t], curr);
            }
        }
    }
    printf("%d\n", dp[last]);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) 
        solve();
}

// Correct Answer
// Execution Time: 0.23
