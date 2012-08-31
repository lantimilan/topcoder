// =========================================================
// 
//       Filename:  prob108E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/16/2011 11:57:45 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

long long taken[1<<20];

int bitcnt(int n)
{
    int ans=0;
    while(n) { n&=n-1; ++ans; }
    return ans;
}

int main()
{
    int n;
    long long y;
    int m;
    cin >> n >> y >> m;
    y-=2001;

    int pred[20]={0};
    for(int i=0; i<m; ++i)
    {
        int a,b; cin >> a >> b; --a,--b;
        pred[b]|=1<<a;
    }

    int seat[20], member[20]; 
    fill(seat,seat+20,-1); fill(member,member+20,-1);
    for(int p=0;p<n;++p) // fill each pos[p]
    {
        for(int prof=0; prof<n; ++prof) 
        if (member[prof]<0)
        {
            seat[p]=prof; member[prof]=p;
            memset(taken,0,sizeof taken);
            taken[(1<<n)-1]=1;
            for(int b=(1<<n)-1; b>=0; b--)
            {
                int k=bitcnt(b); k--; // put prof[k] after fix prof[0..k-1]
                int i;
                if (member[k]>=0) {
                    i=member[k];
                    if ((b&1<<i) && (b&pred[i])==pred[i]) // try prof[k] at pos[i]
                        taken[b^(1<<i)] += taken[b];
                } else {
                    for(i=0; i<n; ++i)
                    if ((b&1<<i) && (b&pred[i])==pred[i]) // try prof[k] at pos[i]
                    {
                        taken[b^(1<<i)] += taken[b];
                    }
                }
            }
            long long cnt=taken[0];
            if (cnt>y) { break; } // fix prof at pos[p]
            else { y-=cnt; seat[p]=-1; member[prof]=-1; }
        }
        if (seat[p]<0) { y=1; break; } // no solution since cannot find a prof fit in pos[p]
    }
    if (y>0) { cout << "The times have changed" << endl; }
    else {
        for(int i=0; i<n; ++i) {
            if (i) { cout << ' '; }
            cout << (seat[i]+1);
        }
        cout << endl;
    }
}

// 705711   Sep 16, 2011 11:31:05 PM    lantimilan  E - Arrangement     GNU C++
// Accepted     1030 ms     9600 KB
// 705634   Sep 16, 2011 10:16:35 PM    lantimilan  D - Basketball Team     GNU
// C++  Accepted    30 ms   1400 KB
// 705612   Sep 16, 2011 9:56:43 PM     lantimilan  C - Dorm Water Supply   GNU
// C++  Accepted    30 ms   1400 KB
// 705581   Sep 16, 2011 9:35:58 PM     lantimilan  B - Datatypes   GNU C++
// Accepted     190 ms  1800 KB
// 705562   Sep 16, 2011 9:26:53 PM     lantimilan  B - Datatypes   GNU C++
// Wrong answer on test 4   10 ms   1400 KB
// 705529   Sep 16, 2011 9:07:43 PM     lantimilan  A - Palindromic Times   GNU
// C++  Accepted    30 ms   1400 KB
//
