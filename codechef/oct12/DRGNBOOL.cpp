// for each level
// sum Soint - sum Sofloat
// take 0 if >0
// take diff

#include <cstdio>
using namespace std;

void solve()
{
    int N, M; scanf("%d%d", &N, &M);
    int soint[105] = {0};
    int sofloat[105] = {0};
    for(int i=0; i<N; ++i) {
        int cap, level; scanf("%d%d", &cap, &level);
        soint[level] += cap;
    }
    for(int i=0; i<M; ++i) {
        int cap, level; scanf("%d%d", &cap, &level);
        sofloat[level] += cap;
    }
    int ans = 0;
    for(int i=1; i<=100; ++i) {
        int diff = sofloat[i] - soint[i];
        if (diff < 0) diff = 0;
        ans += diff;
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) solve();
}

// Correct Answer
// Execution Time: 0.27
