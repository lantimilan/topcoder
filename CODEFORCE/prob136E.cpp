// =========================================================
// 
//       Finame:  prob136E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/21/2011 05:08:40 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/21/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 100005
char line[MAXN];

void solve(const char *line, int ans[])
{
    int nmin=0, nmax=0; // count of 1
    int n=strlen(line); assert(line[n-1]!='?');
    for(int i=0; i<n; ++i) {
        if (line[i]=='0') continue;
        if (line[i]=='1') { ++nmin; ++nmax; }
        if (line[i]=='?') { ++nmax; }
    }

    if (n%2==0) {
        if (nmin <= (n-2)/2) ans[0]=1;
        if (nmax >= (n-2)/2+2) ans[3]=1;
        if (nmin<=n/2 && n/2<=nmax) {
            if (line[n-1]=='0') ans[2]=1;
            if (line[n-1]=='1') ans[1]=1;
            //if (line[n-1]=='?') ans[1]=ans[2]=1;
        }
    }
    else {
        if (nmin <= (n-1)/2) ans[0]=1;
        if (nmax >= (n-1)/2+2) ans[3]=1;
        if (nmin<=(n+1)/2 && (n+1)/2<=nmax) {
            if (line[n-1]=='0') ans[2]=1;
            if (line[n-1]=='1') ans[1]=1;
            //if (line[n-1]=='?') ans[1]=ans[2]=1;
        }
    }
}

int main()
{
    gets(line);
    int n=strlen(line);
    int pos;
    for(pos=n-1; pos>=0 && line[pos]!='?'; --pos)
        ;

    int ans[4]={0}; // 00 01 10 11
    if (pos>=0) {
        line[pos]='0';
        solve(line, ans);
        line[pos]='1';
        solve(line, ans);
    }
    else {
        solve(line, ans);
    }
    const char *str[4]={"00", "01", "10", "11"};
    for(int i=0; i<4; ++i) {
        if (ans[i]) puts(str[i]);
    }
}

// 971100   Dec 22, 2011 5:27:38 AM     lantimilan  E - Zero-One    GNU C++
// Accepted     50 ms   1400 KB
// 971096   Dec 22, 2011 5:20:14 AM     lantimilan  E - Zero-One    GNU C++
// Wrong answer on test 7   30 ms   1400 KB
// 971088   Dec 22, 2011 4:40:14 AM     lantimilan  D - Rectangle and Square
// GNU C++  Accepted    50 ms   1400 KB
// 971085   Dec 22, 2011 4:34:10 AM     lantimilan  D - Rectangle and Square
// GNU C++  Wrong answer on test 7  30 ms   1400 KB
// 971072   Dec 22, 2011 3:29:58 AM     lantimilan  C - Replacement     GNU C++
// Accepted     110 ms  1700 KB
// 971069   Dec 22, 2011 3:16:32 AM     lantimilan  B - Ternary Logic   GNU C++
// Accepted     30 ms   1300 KB
// 971068   Dec 22, 2011 3:16:32 AM     lantimilan  B - Ternary Logic   GNU C++
// Accepted     30 ms   1300 KB
// 971055   Dec 22, 2011 2:33:41 AM     lantimilan  A - Presents    GNU C++
// Accepted     30 ms   1300 KB 
