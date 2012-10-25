// =========================================================
// 
//       Filename:  prob237C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/25/2012 08:51:25 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/25/2012, LI YAN
// 
// =========================================================

// prefix sum
// binary search l

#include <algorithm>
#include <iostream>
using namespace std;

const int M = 1000000+5;
bool isprime[M];
int nprime[M];

void init()
{
    for(int i=2; i<M; ++i)
        isprime[i] = true;

    for(int i=2; i<M; ++i) {
        nprime[i] = nprime[i-1];
        if (isprime[i]) { 
            nprime[i]++;
            for(int j=i+i; j<M; j+=i)
                isprime[j] = false;
        }
    }
    /*
    for(int i=0; i<10; ++i)
        cout << nprime[i] << ' ';
    cout << endl;
    */
}

int main()
{
    init();
    int a, b, k;
    cin >> a >> b >> k;
    
    int lo = -1, hi = b-a+2; // lo is left limit, hi is last good length
    while(lo + 1 < hi) {
        int l = (lo+hi)/2;
        bool good = true;
        for(int x=a; x<=b-l+1; ++x) {
            int num = nprime[x+l-1] - nprime[x-1];
            if (num < k) { good = false; break; }
        }
        //cout << lo << ' ' << hi << ' ' << good << ' ' << l << endl;
        if (good) { hi = l; }
        else { lo = l; }
    }
    if (hi == b-a+2) cout << -1 << endl;
    else cout << hi << endl;
}
