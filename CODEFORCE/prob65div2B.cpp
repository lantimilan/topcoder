// =========================================================
// 
//       Filename:  prob65div2B.cpp
// 
//    Description:  B. Progress Bar
// 
//        Version:  1.0
//        Created:  03/29/2011 03:43:56 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/29/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int cmp(int a[], int len, int level, int t)
{
    int sum=0, target = t*len*level;
    for(int i=0; i<len; ++i) sum +=a[i];
    if (sum*100 < target) return -1;
    else if (sum*100 == target) return 0;
    else return 1;
}

void print(int a[], int len)
{
    for(int i=0; i<len; ++i)
    {
        if (i) cout << " " << a[i];
        else cout << a[i];
    }
    cout << endl;
}

void solve()
{
    int n, k, t;
    cin >> n >> k >> t;
    int a[110] = {0};
    int p=0;
    while(cmp(a,n,k,t) < 0)
    {
        a[p]++;
        if (a[p] > k) { a[p]--; p++; a[p]++; }
    }
    if (cmp(a,n,k,t)==0) print(a,n);
    else { a[p]--; print(a,n); }
}

int main()
{
    solve();
}
