#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

void solve()
{
    int y[60], N;
    int low[60]={0};
    double ans=0.0;
    
    scanf("%d", &N); //printf("N %d\n", N);
    for(int i=0; i<N; ++i) scanf("%d", &y[i]);
    
    sort(y, y+N);
    for(int i=1; i<N; ++i)
    {        
        if (y[i]>y[i-1]) low[i]=i;
        else low[i]=low[i-1];
    }
    for(int i=0; i<N; ++i)
    {
    for(int p=0; p<N; ++p)
    {        
        int m=N-1, z=low[i], big=m-z;        
        if (big==0) {
            ans += 1.0*(p+1)/N;
            continue;
        }
        double f=1.0, curr=0.0;
        for(int l=p-1; l>=0; --l)
        {   
            assert(m>0);         
            curr += f*(p-l)*big/m;            
            f=f*z/m;
            if (z<=0) break;
            --z; --m;
        }
        curr+=f*(p+1);
        ans += curr/N;
        //printf("i %d, p %d, ans %lf\n", i, p, ans);
    }
    }
    printf("%.2lf\n", ans);
}
int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
