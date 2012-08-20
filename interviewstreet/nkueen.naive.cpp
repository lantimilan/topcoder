// =========================================================
// 
//       Filename:  nkueen.cpp
// 
//    Description:  find a solution to place N queen in NxN board
//    the queen is allowed knight's move in addition
// 
//        Version:  1.0
//        Created:  07/21/2012 11:05:05 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/21/2012, LI YAN
// 
// =========================================================

// backtrack solution solves N=32
//
#include <iostream>
using namespace std;

int conf[100];

bool attacked(int i, int j)
{
    for(int r=0; r<i; ++r) {
        if (conf[r] == j) return true;
        if (i+j == r+conf[r]) return true;
        if (i-j == r-conf[r]) return true;
    }

    if (i>=1) {
        if (conf[i-1]==j+2 || conf[i-1]==j-2) return true;
    }
    if (i>=2) {
        if (conf[i-2]==j+1 || conf[i-2]==j-1) return true;
    }
    return false;
}


int main()
{
    int N; cin >> N;

    bool found=true;
    int i, j;
    for(i=0; i<N; ++i) {
        for(j=0; j<N; ++j)
            if (!attacked(i,j)) break;
        conf[i]=j;
        while(conf[i]>=N) {
            --i; 
            if (i<0) break;
            conf[i]++;
            while(conf[i]<N && attacked(i, conf[i]))
                conf[i]++;
        }
        if (i<0) {
            found=false; break;
        }
    }
    if (found) {
        for(int i=0; i<N; ++i) {
            if (i) cout << ' ';
            cout << conf[i]+1;
        }
        cout << endl;
    }
    else {
        cout << "No solution" << endl;
    }
}
