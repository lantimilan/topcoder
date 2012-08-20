// arithprogression
//
// K is sum of all p_k for i<=k<=j
// V is prod of all d_k^p_k * fact[K]
//
// notice that when K>=MOD, V=0
//
#include <cstdio>
#include <cmath>
using namespace std;

const int MOD = 1000000+3;
const int MAXN=100000+5;

struct node_t {
    int id;
    int begin, end;
    long long sum;
    long long prod, base;
    long long extra;
};

node_t vec[2*MAXN];

int N, NN;
int fact[MOD+2];
long long D[MAXN], P[MAXN];

// a^b
int fastpow(long long a, long long b)
{
    int ans=1, f=a;
    while(b) {
        if (b&1) ans = int((long long)ans*f %MOD);
        f = int((long long)f*f % MOD);
        b/=2;
    }
    return ans;
}

int mult(long long a, long long b)
{
    int c = int(a*b %MOD);
    return c;
}

void init()
{
    // factorial
    int k=1;
    for(int p=1; p<MOD; ++p) {
        k = int((long long)k*p%MOD);
        fact[p]=k;
    }
}

void construct()
{
    NN = 2*N-1;
    for(int i=0; i<NN; ++i) {
        vec[i].id=i; vec[i].sum=0;
        vec[i].prod=vec[i].base=1;
        vec[i].extra=0;
    }
    int n=N; while(n&(n-1)) n&=n-1; n=2*n-1;
    for(int i=n, j=0; i<2*n; ) {
        if (i<NN) { 
            vec[i].begin=vec[i].end=j;
            vec[i].sum=P[j]; 
            vec[i].prod=fastpow(D[j],P[j]);
            vec[i].base=D[j];
            ++i; ++j;
        }
        else {
            int p=(i-1)/2;
            vec[p].begin=vec[p].end=j;
            vec[p].sum=P[j]; 
            vec[p].prod=fastpow(D[j],P[j]);
            vec[p].base=D[j];
            i+=2; ++j;
        }
    }
    for(int i=NN-1; i>0; --i) {
        int p=(i-1)/2;
        if (i&1) vec[p].begin=vec[i].begin;
        else vec[p].end=vec[i].end;
        vec[p].sum  += vec[i].sum;
        vec[p].prod = mult(vec[p].prod, vec[i].prod);
        vec[p].base = mult(vec[p].base, vec[i].base);
    }
}

void update(int begin, int end, int id, long long val)
{
    if (begin > vec[id].end || end < vec[id].begin) return;
    if (begin <= vec[id].begin && vec[id].end <= end) {
        vec[id].sum += val*(vec[id].end-vec[id].begin+1);
        vec[id].prod = mult(vec[id].prod, fastpow(vec[id].base, val));
        vec[id].extra+=val;
        return;
    }
    int ll=2*id+1, rr=2*id+2;
    // push extra into children
    if (ll<NN) update(vec[id].begin, vec[id].end, ll, vec[id].extra);
    if (rr<NN) update(vec[id].begin, vec[id].end, rr, vec[id].extra);
    vec[id].extra=0;
    if (ll<NN) update(begin, end, ll, val);
    if (rr<NN) update(begin, end, rr, val);
}

void query(int begin, int end, int id, long long &sum, long long &prod)
{
    if (begin > vec[id].end || end < vec[id].begin) return;
    if (begin <= vec[id].begin && vec[id].end <= end) {
        sum += vec[id].sum; prod = mult(prod, vec[id].prod);
        return;
    }
    int ll=id*2+1, rr=id*2+2;
    if (ll<NN) update(vec[id].begin, vec[id].end, ll, vec[id].extra);
    if (rr<NN) update(vec[id].begin, vec[id].end, rr, vec[id].extra);
    vec[id].extra=0;
    if (ll<NN) query(begin, end, ll, sum, prod);
    if (rr<NN) query(begin, end, rr, sum, prod);
}

int main()
{
    init();
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        int dummy;
        scanf("%d%lld%lld", &dummy, &D[i], &P[i]);
    }
    construct();

    int Q; scanf("%d", &Q);
    for(int q=0; q<Q; ++q) {
        int type; scanf("%d", &type);
        int start, end;
        long long val=0;
        scanf("%d%d", &start, &end); --start, --end;
        if (type==1) scanf("%lld", &val);

        long long ansK=0, ansV=1;
        if (type==0) query(start, end, 0, ansK, ansV);
        else update(start, end, 0, val);

        if (ansV) ansV = mult(ansV, fact[ansK]);
        if (type==0)
        printf("%lld %lld\n", ansK, ansV);
    }
}

// Fri Jan 13 09:33:44 PST 2012
// Use interval tree
//
// ARITHMETIC PROGRESSIONS  C++     
// Time Limit Exceeded
// 2/9 testcases passed
// 3 Point(s)   View Submission     Processed   2012-01-10 00:00 UTC
