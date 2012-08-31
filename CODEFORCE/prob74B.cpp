// =========================================================
// 
//       Filename:  prob74B.cpp
// 
//    Description:  B. Train
// 
//        Version:  1.0
//        Created:  04/15/2011 08:41:00 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/15/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void adjust(int &k, int n)
{ if (k<1) k=1; if (k>n) k=n; }

void solve()
{
    int n,S,C; cin >> n >> S >> C;
    string sdir; cin >> sdir; cin >> sdir;
    int dir = (sdir=="head") ? -1 : 1;
    string train; cin >> train;
    int min=0;
    for(int i=0; i<int(train.size())-1; ++i)
    {
    //cout << C << " " << S << endl;
        assert(C!=S);
        if (train[i] == '0')
        {
            if (dir*(S-C)>0) { S+=dir; adjust(S,n); }
            else { S-=dir; adjust(S,n); }
            C += dir;
        }
        else
        {
            C += dir;
            if (C==1) S=n; 
            else if (C==n) S=1;
            else if (dir>0) S=1; 
            else S=n;
        } 
        if (C==1 || C==n) dir=-dir; 
        if (S==C) { min=i+1;break; }
    }
    if (S==C) cout << "Controller " << min << endl;
    else cout << "Stowaway\n";
}
int main()
{
    solve();
}

/* **************
 * surprsingly tricky, or I am just too dumb
 * in contest misread the init pos of C and S, it is n S C, so never
 * understand the example.
 *
 * When offline, the edge case when hit 1 or n got wrong several times
 *
 * 393331        Apr 16, 2011 1:42:45 AM    lantimilan        B - Train      GNU
 * C++       Accepted        30 ms       1400 KB
 * 393311   Apr 16, 2011 1:12:46 AM     lantimilan  B - Train   GNU C++
 * Wrong answer on test 2   10 ms   1400 KB
 * 393180   Apr 15, 2011 11:20:16 PM    lantimilan  B - Train   GNU C++
 * Wrong answer on test 3   10 ms   1400 KB 
 * */
