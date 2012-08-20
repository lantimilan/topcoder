// countscoreboard.cpp
//
#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
const int MOD=1000000000+7;

map<pair<pii,pii>,int> memo;
int fact[50];
int N, P, M; // plus, minus
int a[50];

void refadd(int &a, int b)
{
    a=((int64)a+b)%MOD;
}

int add(int a, int b)
{
    return ((int64)a+b)%MOD;
}

int mult(int a, int b)
{
    return (int64)a*b%MOD;
}

void init()
{
    fact[0]=1;
    for(int i=1; i<=40; ++i)
        fact[i]=mult(fact[i-1], i);
}

int calc(int pos, int plus, int last, int total)
{
    if (pos==0) return plus==0 && total==0;
    pair<pii,pii> entry=make_pair(pii(pos,plus), pii(last,total));
    if (memo.count(entry)) return memo[entry];
    int &ans=memo[entry]; ans=0;
    if (plus && total>=a[plus-1]) // use a[plus-1] to end
        refadd(ans, calc(pos-1, plus-1, a[plus-1], total-a[plus-1]));
    int minus=pos-plus; // use -1 to end
    if (minus) {
        int small=(total+pos-1)/pos; if (plus && a[plus-1]>small) small=a[plus-1];
        int large=min(last, total-(pos-1)*(pos-2)/2);
        for(int i=small; i<=large; ++i)
            refadd(ans, calc(pos-1, plus, i, total-i));
    }
    return ans;
}

void solve()
{
    scanf("%d", &N);
    P=M=0;
    for(int i=0; i<N; ++i) {
        int t; scanf("%d", &t);
        if (t<0) ++M;
        else a[P++]=t;
    }
    sort(a, a+P);
    memo.clear();
    int total = N*(N-1)/2;
    int ans = calc(N, P, N, total);
    ans = mult(ans, fact[M]);
    printf("%d\n", ans);
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
