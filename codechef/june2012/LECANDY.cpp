#include <cstdio>
using namespace std;

void solve()
{
    int N, C; scanf("%d%d", &N, &C);
    for(int i=0; i<N; ++i) {
        int x; scanf("%d", &x);
        C-=x;
    }
    if (C<0) puts("No");
    else puts("Yes");
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) solve();
}
