// =========================================================
// 
//       Filename:  LUCKY8.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/01/2012 09:54:04 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <map>
using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef pair<int64,int64> pll;
typedef pair<pii,pll> pkk;

map<pkk,int> memo;

template<class T>
void chmax(T &a, T b)
{
    a=(a>b)?a:b;
}

int calc(int four, int seven, int64 factor, int64 low, int64 high)
{
    if (factor<=0) return four * seven;
    pkk mykey = (pkk(pii(four,seven), pll(low,high)));
    if (memo.count(mykey))
        return memo[mykey];
    int dlow, dhigh;
    int64 remlow, remhigh;
    dlow = low/factor; dhigh=high/factor;
    remlow = low%factor; remhigh = high%factor;

    int ans=0;
    int64 newlow, newhigh; 
    // try 4
    if (dlow<=4 && 4<=dhigh) {
        newlow=remlow; newhigh=remhigh;
        if (dlow < 4) newlow=0;
        if (4 < dhigh) newhigh=factor-1;
        chmax(ans, calc(four+1, seven, factor/10, newlow, newhigh));
    }
    // try 7
    if (dlow<=7 && 7<=dhigh) {
        newlow=remlow; newhigh=remhigh;
        if (dlow < 7) newlow=0;
        if (7 < dhigh) newhigh=factor-1;
        chmax(ans, calc(four, seven+1, factor/10, newlow, newhigh));
    }
    // try other
    if (dlow==dhigh) {
        newlow=remlow; newhigh=remhigh;
        chmax(ans, calc(four, seven, factor/10, newlow, newhigh));
    }
    else if (dlow+1 == dhigh) {
        // use dlow
        chmax(ans, calc(four, seven, factor/10, remlow, factor-1));
        // use dhigh
        chmax(ans, calc(four, seven, factor/10, 0, remhigh));
    }
    else {
        // use dlow < d < dhigh
        chmax(ans, calc(four, seven, factor/10, 0, factor-1));
    }
    return memo[mykey]=ans;
}

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        int64 L, R; scanf("%lld%lld", &L, &R);
        int64 factor=(int64)1.0e18;
        int ans = calc(0, 0, factor, L, R);
        printf("%d\n", ans);
    }
}
