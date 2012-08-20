// =========================================================
// 
//       Filename:  tictactoe2.cpp
// 
//    Description:  use DP to make optimal move
// 
//        Version:  1.0
//        Created:  06/24/2012 10:52:25 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/24/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
using namespace std;


const int N=3;

int dp[1<<20][3]; // the actual move
int win[1<<20][3]; // +1 win, 0 draw, +2 lose
//
// [0 1 2
//  3 4 5
//  6 7 8]
//
int encode(int b[])
{
    int ans=0;
    int f=1;
    for(int i=0; i<N*N; ++i) {
        ans += b[i]*f;
        f *= N;
    }
    return ans;
}

void decode(int k, int a[])
{
    for(int i=0; i<N*N; ++i) {
        a[i] = k%N;
        k/=N;
    }
}

bool iswin(int a[], int turn)
{
    // check row
    for(int i=0; i<N; ++i)
    {
        if (turn == a[N*i] && a[N*i] == a[N*i+1] && a[N*i] == a[N*i+2])
            return true;
    }
    // check col
    for(int i=0; i<N; ++i)
    {
        if (turn == a[i] && a[i] == a[i+N] && a[i] == a[i+2*N])
            return true;
    }
    // check (0,0) to (N-1,N-1)
    if (turn == a[0] && a[0] == a[4] && a[0] == a[8])
        return true;
    // check (N-1,0) to (0,N-1)
    if (turn == a[2] && a[2] == a[4] && a[4] == a[6])
        return true;

    return false;
}

int move(int conf, int turn)
{
    if (win[conf][turn]>=0) return win[conf][turn];
    int a[N*N];
    decode(conf, a);
    if (iswin(a, turn)) return 1;
    if (iswin(a, 3-turn)) return 2;
    bool done=true;
    for(int i=0; i<N*N; ++i)
        if (a[i]==0) done=false;
    if (done) return 0;

    for(int i=0; i<N*N; ++i) if (a[i]==0) {
        a[i]=turn;
        int newconf = encode(a);
        if (move(newconf, 3-turn)==2) { // win
            dp[conf][turn] = i;
            win[conf][turn]= 1;
            return 1;
        }
        else if (move(newconf, 3-turn)==0) { // draw
            dp[conf][turn]=i;
            win[conf][turn]=0;
        }
        else {
            if (win[conf][turn]<0) {
                dp[conf][turn]=i;
                win[conf][turn]=2;
            }
        }
        a[i]=0;
    }
    return win[conf][turn];
}

int main()
{
    memset(win, -1, sizeof win);
    int turn;
    int a[N*N];
    cin >> turn;
    for(int i=0; i<N*N; ++i) {
        cin >> a[i];
        if (a[i]<0) a[i]=0;
    }
    int res = move(encode(a), turn);
    int ans = dp[encode(a)][turn];
    //cout << res << endl;
    //cout << ans << endl;
    cout << (ans/N) << ' ' << (ans%N) << endl;
}

// brute force on all possible states
// it never loses but could tie with another perfect player
