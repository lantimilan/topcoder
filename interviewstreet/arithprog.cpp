// arithprogression
//
// K is sum of all p_k for i<=k<=j
// V is prod of all d_k^p_k * fact[K]
//
// notice that when K>=MOD, V=0
//
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int MOD = 1000000+3;
const int MAXN= 100000+5;

struct node_t {
    int id;
    int begin, end;
    long long sum;
    int prod;
    int base;
    int extra;
};

node_t vec[2*MAXN];

int N, NN;
int fact[MOD+2];
int D[MAXN], P[MAXN];

int mult(int a, int b)
{
    return (long long)a*b %MOD;
}

// a^b
int fastpow(int a, int b)
{
    int ans=1, f=a;
    while(b) {
        if (b&1) ans = mult(ans, f);
        f = mult(f, f);
        b/=2;
    }
    return ans;
}

void init()
{
    // factorial
    fact[0]=1;
    for(int p=1; p<MOD; ++p) {
        fact[p]=mult(fact[p-1],p);
    }
    //for(int i=0; i<10; ++i) printf("%d ", fact[i]); putchar('\n');
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

int update(int begin, int end, int id, int val)
{
    int pp=1, p1=1, p2=1;
    if (begin > vec[id].end || end < vec[id].begin) return 1;
    if (begin <= vec[id].begin && vec[id].end <= end) {
        vec[id].sum += (long long)val*(vec[id].end-vec[id].begin+1);
        pp = fastpow(vec[id].base, val);
        vec[id].prod = mult(vec[id].prod, pp);
        vec[id].extra+=val; // extra <=Q*v=10^5*10^4=10^9 fits 32bit int
        return pp;
    }
    int ll=2*id+1, rr=2*id+2;
    // push extra into children
    if (ll<NN) update(vec[id].begin, vec[id].end, ll, vec[id].extra);
    if (rr<NN) update(vec[id].begin, vec[id].end, rr, vec[id].extra);
    vec[id].extra=0;
    if (ll<NN) p1=update(begin, end, ll, val);
    if (rr<NN) p2=update(begin, end, rr, val);
    // update curr node
    int d1=max(vec[id].begin, begin);
    int d2=min(vec[id].end, end);
    vec[id].sum += (long long)val*(d2-d1+1);
    pp = mult(p1,p2);
    vec[id].prod = mult(vec[id].prod, pp);
    return pp;
}

void query(int begin, int end, int id, long long &sum, int &prod)
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
        scanf("%d%d%d", &dummy, &D[i], &P[i]);
    }
    construct();

    int Q; scanf("%d", &Q);
    for(int q=0; q<Q; ++q) {
        int type; scanf("%d", &type);
        int start, end;
        int val=0;
        scanf("%d%d", &start, &end); --start, --end;
        if (type==1) scanf("%d", &val);

        long long ansK=0;
        int ansV=1;
        if (type==0) query(start, end, 0, ansK, ansV);
        else update(start, end, 0, val);

        if (ansK<MOD) ansV = mult(ansV, fact[ansK]);
        else ansV=0;

        if (type==0)
        printf("%lld %d\n", ansK, ansV);
    }
}

// after fixed a very stupid mistake, 
// in update() function, forgot to update parent after process children
// got AC
//
// had two WA to fix this bug, another one is forgot compute intersection
// when updating parent's vec[id].sum
// now back to 13
//
// Wed Feb 22 21:14:06 PST 2012
// Rank:  13  Score:  833.00  
//
//  Language    Time    Status  Result  
//  ARITHMETIC PROGRESSIONS     cpp     2012-02-23 10:42:09     Processed   Accepted    View Details
//  ARITHMETIC PROGRESSIONS     cpp     2012-02-23 10:31:44     Processed   Wrong Answer
//  3/9 testcases passed
//      View Details
//      ARITHMETIC PROGRESSIONS     cpp     2012-02-22 23:36:45     Processed   Wrong Answer
//      3/9 testcases passed
//          View Details
//
// Fri Jan 13 09:33:44 PST 2012
// Use interval tree
//
// ARITHMETIC PROGRESSIONS  C++     
// Wrong Answer
// 3/9 testcases passed
// 7 Point(s)   View Submission     Processed   2012-01-13 18:21 UTC
//
// ARITHMETIC PROGRESSIONS  C++     
// Segmentation fault
// 3/9 testcases passed
// 7 Point(s)   View Submission     Processed   2012-01-13 18:06 UTC
//
// ARITHMETIC PROGRESSIONS  C++     
// Time Limit Exceeded
// 2/9 testcases passed
// 3 Point(s)   View Submission     Processed   2012-01-10 00:00 UTC
