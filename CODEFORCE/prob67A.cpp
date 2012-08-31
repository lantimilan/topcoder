// =========================================================
// 
//       Filename:  prob67A.cpp
// 
//    Description:  A. Life Without Zeros
// 
//        Version:  1.0
//        Created:  04/13/2011 08:02:27 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/13/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int process(int k)
{
    int res=0,tmp=1;
    while(k) { 
        int d=k%10; k/=10; // watch integer overflow here
        if (d) { res=tmp*d+res; tmp*=10; } 
    }
    return res;
}
void solve()
{
    string yes="YES", no="NO";
    int a,b; cin >> a >> b; int c = a+b;
    a=process(a); b=process(b); c=process(c);
    if (a+b==c) cout << yes << endl;
    else cout << no << endl;
}
int main()
{
    solve();
}

// failed on case: 999999999 999999999
// integer overflow when 8999999991 
