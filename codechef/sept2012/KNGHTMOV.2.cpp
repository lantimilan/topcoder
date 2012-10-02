// =========================================================
// 
//       Filename:  KNGHTMOV.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/KNGHTMOV
// 
//        Version:  1.0
//        Created:  09/08/2012 08:00:30 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/08/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;

const int MOD=1e9+7;
const int MAX=200000;

int dp[1<<15][20]; // mask, last
int fact[MAX];
int bitcnt[1<<15];

void refadd(int &a, int b)
{
    a = ((int64)a+b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a * b %MOD;
}

int getfact(int n)
{
    if (n<MAX) return fact[n];
    int ans = fact[MAX-1];
    for(int i=MAX; i<=n; ++i)
        ans = ((int64)ans * i) % MOD;
    return ans;
}

int getbitcnt(int n)
{
    int ans=0;
    while(n) {
        n&=n-1;
        ans++;
    }
    return ans;
}

void init()
{
    fact[0] = fact[1] = 1;
    for(int i=2; i<MAX; ++i)
        fact[i] = mult(fact[i-1], i);

    for(int i=0; i<(1<<15); ++i)
        bitcnt[i] = getbitcnt(i);
}

int fastpow(int a, int b)
{
    int ans = 1;
    int f = a;
    while(b) {
        if (b&1) {
            ans = (int64)ans * f % MOD;
        }
        b/=2;
        f = (int64)f * f % MOD;
    }
    return ans;
}

int intinv(int a)
{
    return fastpow(a, MOD-2);
}

int comb(int n, int k)
{
    int ans;
    //assert(n<2000);
    ans = getfact(n);
    ans = (int64)ans * intinv(getfact(k)) % MOD;
    ans = (int64)ans * intinv(getfact(n-k)) % MOD;
    return ans;
}

int det(int ax, int ay, int bx, int by)
{
    return ax*by - ay*bx;
}

int inv(const int a[][2], int b[][2])
{
    b[1][1] = -a[0][0];
    b[0][0] = -a[1][1];
    b[0][1] = a[0][1];
    b[1][0] = a[1][0];
    return a[0][1]*a[1][0] - a[0][0]*a[1][1];
}

bool eqnsolve(const int a[][2], const int b[], int c[])
{
    int div;
    int pre[2][2];
    div = inv(a, pre);
    c[0] = pre[0][0] * b[0] + pre[0][1] * b[1];
    c[1] = pre[1][0] * b[0] + pre[1][1] * b[1];
    if (c[0] % div || c[1] % div) return false;
    c[0] /= div;
    c[1] /= div;
    return c[0]>=0 && c[1]>=0;
}

int getmove(const int a[][2], int b[])
{
    int ans;
    int c[2];
    bool good;
    good = eqnsolve(a, b, c);
    if (good) ans = comb(c[0]+c[1], c[0]);
    else ans = 0;

    return ans;
}

// one of two moves is (0,0),
// the other is non-zero (ax,ay)
// target is (xx,yy)
int simple(int ax, int ay, int xx, int yy)
{
    if (xx==0 && yy==0) return -1; // use c1 for move (0,0)
    if (ax==0) {
        assert(ay!=0);
        if (xx==0) {
            if (yy % ay == 0 && yy/ay>=0) return -1;
            else return 0;
        }
        else return 0;
    }
    else if (ay==0) {
        assert(ax!=0);
        if (yy==0) {
            if (xx % ax == 0 && xx/ax>=0) return -1;
            else return 0;
        }
        else return 0;
    }
    else {
        assert(ax!=0 && ay!=0);
        if (xx%ax == 0 && yy%ay == 0 &&
            xx/ax>=0 && yy/ay>=0) 
            return -1;
        else return 0;
    }
}

int vecdiv(int ax, int ay, int xx, int yy)
{
    if (ax!=0) return xx/ax;
    else return yy/ay;
}

int gcd(int a, int b)
{
    if (b==0) return a;
    else return gcd(b, a%b);
}

void solve()
{
    int X, Y, K; assert(scanf("%d%d%d", &X, &Y, &K) == 3);
    int AX, AY, BX, BY;
    assert(scanf("%d%d%d%d", &AX, &AY, &BX, &BY) == 4);
    //printf("AX %d AY %d BX %d BY %d\n", AX, AY, BX, BY);
    int block[20][2];
    for(int i=0; i<K; ++i) {
        assert(scanf("%d%d", &block[i][0], &block[i][1]) == 2);
    }

    int ans;
    // need non-negative (c1,c2) for the two moves
    // both moves are (0,0)
    if (AX==0 && AY==0 && BX==0 && BY==0) {
        if (X==0 && Y==0) ans=-1; // inf to move (0,0) to (0,0)
        else ans = 0;
        printf("%d\n", ans); return;
    }
    // solve one of move is (0,0) and the other is not
    if (AX==0 && AY==0) {
        ans = simple(BX, BY, X, Y);
        printf("%d\n", ans);
        return;
    }
    if (BX==0 && BY==0) {
        ans = simple(AX, AY, X, Y);
        printf("%d\n", ans);
        return;
    }
    // solve both moves are not (0,0)
    if (det(AX, AY, BX, BY) == 0) { // two moves are dependent
        if (det(AX, AY, X, Y) == 0) { 
            // need only solve
            // AX * c1 + BX * c2 = X
            if (X%gcd(AX,BX) == 0) {
                if (AX==0) {
                    if (X*BX>=0) ans = -1;
                    else ans = 0;
                }
                else if (BX==0) {
                    if (X*AX>=0) ans = -1;
                    else ans = 0;
                }
                else {
                    ans = (AX*BX <= 0);
                }
            }
            else ans = 0;
        }
        else ans = 0;
        printf("%d\n", ans);
        return;
    }
    // (AX, AY) and (BX, BY) are independent
    // | AX BX | |c1| = |X|
    // | AY BY | |c2|   |Y|
    // has exactly one solution
    int a[2][2];
    int b[2];

    a[0][0] = AX; a[0][1] = BX;
    a[1][0] = AY; a[1][1] = BY;
    b[0] = X; b[1] = Y;

    ans = getmove(a, b);
    printf("base ans %d\n", ans);
    // inclusion-exclusion to get union of 
    // all K blocks
    //
    //memset(dp, 0, sizeof dp);
    // basecase: mask with one bit set
    for(int j=0; j<K; ++j) {
        memcpy(b, block[j], sizeof b);
        dp[1<<j][j] = getmove(a, b);
    }
    // recursive step
    for(int mask=1; mask < (1<<K); ++mask) 
    //if (bitcnt(mask)>1)
    if (bitcnt[mask]>1)
    {
        for(int j=0; j<K; ++j) if (mask & 1<<j) {
            int curr = 0;
            int sub = mask & ~(1<<j);
            int move;
            for(int x=0; x<K; ++x) if (sub & 1<<x) 
            {
                // move from block[x] to block[j]
                b[0] = block[j][0] - block[x][0];
                b[1] = block[j][1] - block[x][1];
                move = mult(dp[sub][x], getmove(a,b));
                refadd(curr, move);
            }
            dp[mask][j] = curr;
        }
    }

    for(int mask=1; mask < (1<<K); ++mask) {
        for(int j=0; j<K; ++j) if (mask & 1<<j) {
            int curr = dp[mask][j];
            int move;
            // move block[j] to (X,Y)
            b[0] = X - block[j][0];
            b[1] = Y - block[j][1];
            move = getmove(a, b);
            curr = mult(curr, move);
            //printf("mask %d, last %d, curr %d\n", mask, j, curr);
            //if (bitcnt(mask) & 1) {
            if (bitcnt[mask] & 1) {
                ans -= curr;
                if (ans < 0) ans += MOD;
            }
            else {
                ans += curr;
                if (ans >= MOD) ans -= MOD;
            }
        }
    } 

    printf("%d\n", ans);
}

int main()
{
    init();
    int T; assert(scanf("%d", &T) == 1);
    while(T--)
        solve();
}

// why TLE?
// TLE, not too bad
//
