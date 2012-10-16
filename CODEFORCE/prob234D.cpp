// =========================================================
// 
//       Filename:  prob234D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 12:52:58 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, k; fin >> n >> k;
    int fav[105] = {0};
    for(int i=0; i<k; ++i) {
        int t; fin >> t;
        fav[t] = 1;
    }
    int m; fin >> m;
    int bestmin=-1, bestmax=-1;
    int mincnt[105] = {0};
    int maxcnt[105] = {0};
    for(int i=0; i<m; ++i) {
        string title; fin >> title;
        int d; fin >> d;
        int hit = 0;
        int zero = 0;
        int other = 0;
        for(int x=0; x<d; ++x) {
            int b; fin >> b;
            if (b==0) zero++;
            else { 
                if (fav[b]) hit++;
                else other++;
            }
        }
        mincnt[i] = hit + max(0, zero-(n-k-other));
        maxcnt[i] = min(k, zero + hit);
        bestmin = max(mincnt[i], bestmin);
        bestmax = max(maxcnt[i], bestmax);
        //cout << mincnt[i] << ' ' << maxcnt[i] << endl;
    }
    for(int i=0; i<m; ++i) {
        int ans = 2;
        for(int j=0; j<m; ++j) if (j!=i) {
            if (mincnt[j] > maxcnt[i]) ans = 1;
        }
        bool good = true;
        for(int j=0; j<m; ++j) if (j!=i) {
            if (mincnt[i] < maxcnt[j]) good = false;
        }
        if (good) ans = 0;
        fout << ans << endl;
    }
}
