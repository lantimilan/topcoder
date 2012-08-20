// ptinplane.cpp
//
// min turn is easy
// how to count
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
int N; 

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
    if (cnt[mask][score]>=0) { return cnt[mask][score]; }
    if (calc(mask)>score) { return 0; }

    cnt[mask][score]=0;
    for(int b=1; b<(1<<N); ++b) if ((b&mask)==b && coll[b])
    {
        int sub=count(mask^b, score-1);
        cnt[mask][score] = int(((long long)cnt[mask][score] + sub)%MOD);
    }
    //printf("mask %d score %d cnt %d\n", mask, score, cnt[mask][score]);
    return cnt[mask][score];
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
    int ans = calc(mask); printf("ans %d\n", ans);
    //int num = count(mask, ans);
    //printf("%d %d\n", ans, num);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
