// lego block
//
//Lego Blocks 	C++ 	
//Submission Accepted
//10/10 testcases passed
//50 Point(s)
//  View Submission 	Processed 	2012-01-09 05:42 UTC
    
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000007;
int row[1005];
int all[1005];
int nonsplit[1005];

int add(int a, int b)
{
    int c = int(((long long)a+b)%MOD);
    return c;
}

int sub(int a, int b)
{
    int c = a-b; if (c<0) c+=MOD;
    return c;
}

int mult(int a, int b)
{
    int c = int((long long)a*b %MOD);
    return c;
}

// a^b
int fastpow(int a, int b)
{
    int ans=1;
    int f=a;
    while(b) {
        if (b&1) ans=mult(ans, f);
        f = mult(f,f);
        b/=2;
    }
    return ans;
}

void solve()
{
    int N, M; scanf("%d%d", &N, &M);
    memset(row, 0, sizeof row);
    row[0]=1;
    for(int c=0; c<M; ++c) {
        for(int b=1; b<=4; ++b) if (b+c<=M)
            row[b+c] = add(row[b+c], row[c]);
    }
    for(int w=1; w<=M; ++w) {
        all[w]=fastpow(row[w],N);
    }

    for(int w=1; w<=M; ++w) {
        nonsplit[w]=all[w];
        for(int s=1; s<w; ++s) {
            int decr = mult(nonsplit[s],all[w-s]);
            nonsplit[w] = sub(nonsplit[w], decr);
        }
    }
    int ans = nonsplit[M];
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
