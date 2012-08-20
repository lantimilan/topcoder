#include <cstdio>
using namespace std;

void solve()
{
    int N; scanf("%d", &N);
    int best=1;
    for(int i=2; i*i<=N; ++i) if (N%i==0) best=i;
    int ans = N/best - best;
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) solve();
}
