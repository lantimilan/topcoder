// ptinplane.cpp
//
// min turn is easy
// how to count
// 
// can count all in-ordering seq and mult by k! where k is opt move
// dp[mask][k] is number of in-order seqs
// start from first 1 entry, try all singleton and two pt lines
//
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

const int INF=100;
const int MOD=1000000000+7;
int turn[1<<16];
bool coll[1<<16];
int cnt[1<<16][10];
pii pts[20];
int fact[20];
int N; 

void refadd(int &a, int b)
{
    a=((long long)a+b)%MOD;
}

int mult(int a, int b)
{
    return (long long)a*b %MOD;
}

void init()
{
    fact[0]=1;
    for(int i=1; i<=16; ++i) fact[i]=mult(fact[i-1],i);
}

bool collinear(pii p1, pii p2, pii p3)
{
    int x1,x2,x3, y1,y2,y3;
    x1=p1.first; y1=p1.second;
    x2=p2.first; y2=p2.second;
    x3=p3.first; y3=p3.second;
    return (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1) ==0;
}

int calc(int mask)
{
    if (coll[mask]) { return 1; } // only 1 pt in mask
    if (turn[mask]<INF) { return turn[mask]; }

    int x;
    for(x=0; x<N; ++x) if (mask & 1<<x) break;
    assert(x<N);
    // process 2 pts
    for(int i=0; i<N; ++i) if (i!=x && (mask & 1<<i)) {
        int newmask = mask^(1<<x | 1<<i);        
        for(int j=0; j<N; ++j) if (newmask & 1<<j) {
            if (coll[1<<x | 1<<i | 1<<j]) newmask ^= 1<<j;
        }        
        int curr = 1+calc(newmask);
        if (curr < turn[mask]) { 
            turn[mask]=curr;         
        }        
    }
    return turn[mask];
}

int count(int mask, int score)
{    
    //printf("count mask %d score %d\n", mask, score);
    if (score==1) return coll[mask];
    if (calc(mask)>score) { return 0; }
    if (cnt[mask][score]>=0) { return cnt[mask][score]; }

    int x,y;
    int &ans=cnt[mask][score];
    ans=0;
    for(x=0; x<N; ++x) { if (mask & 1<<x) break; }
    assert(x<N);
    refadd(ans, count(mask&~(1<<x), score-1));

    for(y=x+1; y<N; ++y) if (mask & 1<<y) {
        int b=1<<x | 1<<y;
        int bb=0;
        for(int z=y+1; z<N; ++z) if (mask & 1<<z) {
            if (coll[b|1<<z]) bb|=1<<z;
        }
        // try all subsets of bb
        int newmask=mask&~b;
        refadd(ans, count(newmask, score-1)); // x,y only
        for(int z=bb; z>0; z=(z-1)&bb) { // other subsets
            refadd(ans, count(newmask&~z, score-1));
        }
    }
    return ans;
    //cnt[mask][score]=0;
    //for(int b=1; b<(1<<N); ++b) if ((b&mask)==b && coll[b])
    //{
    //    int sub=count(mask^b, score-1);
    //    cnt[mask][score] = int(((long long)cnt[mask][score] + sub)%MOD);
    //}
    //printf("mask %d score %d cnt %d\n", mask, score, cnt[mask][score]);
    //return cnt[mask][score];
}

void solve()
{
    scanf("%d", &N);        
    for(int i=0; i<N; ++i) {
        scanf("%d%d", &pts[i].first, &pts[i].second);
    }
    memset(cnt, -1, sizeof cnt);
    for(int i=0; i<(1<<N); ++i) {
        turn[i]=INF;
    }
    for(int b=0; b<(1<<N); ++b) {
        int bitcnt=0;
        pii p1, p2;
        bool iscoll=true;
        for(int i=0; i<N; ++i) if (b & 1<<i) {
            if (bitcnt==0) { bitcnt++; p1=pts[i]; }
            else if (bitcnt==1) { bitcnt++; p2=pts[i]; }
            else if (!collinear(p1,p2,pts[i])) { iscoll=false; break; }
        }
        coll[b]=iscoll;
    }
    int mask=(1<<N)-1;
    int ans = calc(mask); //printf("ans %d\n", ans);
    int num = count(mask, ans);
    printf("%d %d\n", ans, mult(num, fact[ans]));
}

int main()
{
    init();
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// something useful to keep in mind
// to generate all subsets of a bit pattern
// let bb be the bit pattern
// then
// for(int z=bb; z>0; z=(z-1)&bb) // generates all subsets except empty set which is 0
// {
// }
//
// Points in a Plane    cpp     2012-02-28 09:37:27     Processed   Accepted
// Score: 40
//  View Details
//
//  This is very stupid, missed mask |= 1<<z, I was writing mask |= z
//  and forgot to check mask & 1<<z, two unnecessary WA
//
//  Points in a Plane   cpp     2012-02-28 09:32:58     Processed   Wrong Answer
//  1/10 testcases passed
//  Score: 3
//      View Details
//      Points in a Plane   cpp     2012-02-28 09:25:31     Processed   Wrong Answer
//      1/10 testcases passed
//      Score: 3
//          View Details
//
//  with that I passed sjtu_pigoneand and become 13th
//
//  Rank    Hacker  Country     Score   Submissions     Solved
//  11  diogoaos    Brazil  950.00  67  26
//  11  HaiboHuang  China   950.00  47  26
//  13  lantimilan  USA     943.00  103     26
//  14  sjtu_pigoneand  China   940.00  45  26
//  15  TNBlin  China   867.00  51  23
//  16  Zero    Belarus     844.00  38  23
//  17  olimpo  USA     819.00  87  22
//  18  jin.ubc     Canada  813.00  44  22
//  19  megaterik   Belarus     812.00  105     24
//  20  turuthok    USA     802.00  63  21
