// =========================================================
// 
//       Filename:  prob65div2D.cpp
// 
//    Description:  D. Solitaire
// 
//        Version:  1.0
//        Created:  03/29/2011 04:25:54 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/29/2011, LI YAN
// 
// =========================================================
//
// what I like most: 
// - convert() function uses string "A23456789AJQK"
// - overlap() function, a simple way to test whether two 3x3 intersect
#include <cassert>
#include <map>
#include <iostream>
#include <string>
using namespace std;

string deck[20][20];
int R, C;

bool inbound(int r, int c)
{ return r+3<=R && c+3<=C; }

bool distinct()
{
    map<string,int> mcnt;
    for(int r=0; r<R; ++r) for(int c=0; c<C; ++c)
    {    
        mcnt[deck[r][c]]++; 
        if (mcnt[deck[r][c]] > 1) return false;
    }
    return true;
}

// same suite or all diff rank
bool good(int r1, int c1)
{
    assert(inbound(r1,c1));
    
    bool goodsuite = true, goodrank = true;;
    char suite = deck[r1][c1][1];
    int cnt[300] = {0};
    for(int r=r1; r<r1+3; ++r)
    for(int c=c1; c<c1+3; ++c)
    {
        if (deck[r][c][1] != suite) { goodsuite = false; }
        cnt[int(deck[r][c][0])]++;
        if (cnt[int(deck[r][c][0])] > 1) { goodrank = false; }
    }
    return goodsuite || goodrank;
}

bool overlap(int r1, int c1, int r2, int c2)
{
    assert(inbound(r1,c1) && inbound(r2,c2));

    for(int r=r1; r<r1+3; ++r)
    for(int c=c1; c<c1+3; ++c)
        if (r2<=r && r<r2+3 && c2<=c && c<c2+3)
            return true;
    return false;
}

string convert(int rank, int suite)
{
    string res(2,' ');
    char chrank[] = "A23456789TJQK";
    char chsuite[] = "CDHS";
    res[0] = chrank[rank-1]; res[1] = chsuite[suite-1];
    return res;
}

void solve()
{
    cin >> R >> C;
    for(int r=0; r<R; ++r) for(int c=0; c<C; ++c) cin >> deck[r][c];
        
    int rj1=-1, cj1=-1, rj2=-1, cj2=-1;
    for(int r=0; r<R; ++r) for(int c=0; c<C; ++c)
    {
        if (deck[r][c] == "J1") { rj1=r; cj1 = c; }
        if (deck[r][c] == "J2") { rj2=r; cj2 = c; }
    }

    bool solved = false;
    int resr1, resc1, resr2, resc2;
    string resjoker1, resjoker2;

    // for each card of J1 
    // for each card of J2
    for(int rank1=1; rank1<=13; ++rank1)
    for(int suite1=1; suite1<=4; ++suite1)
    for(int rank2=1; rank2<=13; ++rank2)
    for(int suite2=1; suite2<=4; ++suite2)
    {
        string joker1 = convert(rank1, suite1);
        string joker2 = convert(rank2, suite2);

        if (rj1 >= 0) deck[rj1][cj1] = joker1;
        if (rj2 >= 0) deck[rj2][cj2] = joker2;
        if (!distinct()) continue;

        for(int r1=0; r1+3<=R; ++r1)
        for(int c1=0; c1+3<=C; ++c1)
        for(int r2=0; r2+3<=R; ++r2)
        for(int c2=0; c2+3<=C; ++c2)
        {
            if (good(r1,c1) && good(r2,c2) && 
                !overlap(r1,c1,r2,c2))
                {
                    //cout << joker1 << " " << joker2 << endl;
                    solved = true;
                    resr1 = r1; resc1 = c1;
                    resr2 = r2; resc2 = c2;
                    resjoker1 = joker1; resjoker2 = joker2;
                    goto done;
                }
        }
    }

    done:
    if (solved)
    {
        cout << "Solution exists.\n";
        if (rj1<0 && rj2<0) cout << "There are no jokers.\n";
        else if (rj1>=0 && rj2>=0) cout << "Replace J1 with " << resjoker1 << " and J2 with " << resjoker2 << ".\n";
        else if (rj1>=0) cout << "Replace J1 with " << resjoker1 << ".\n";
        else if (rj2>=0) cout << "Replace J2 with " << resjoker2 << ".\n";
        cout << "Put the first square to (" << (resr1+1) << ", " << (resc1+1) << ").\n";
        cout << "Put the second square to (" << (resr2+1) << ", " << (resc2+1) << ").\n";
    }
    else
    {
        cout << "No solution.\n";
    }
}
int main()
{
    solve();
}

