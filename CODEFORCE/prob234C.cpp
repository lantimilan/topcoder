// =========================================================
// 
//       Filename:  prob234C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 12:27:16 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <fstream>
using namespace std;

int pos[100000+5];
int zero[100000+5];

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n; fin >> n;
    for(int i=0; i<n; ++i) {
        if (i==0) { zero[i] = pos[i] = 0; }
        else { zero[i] = zero[i-1]; pos[i] = pos[i-1]; }
        int k; fin >> k;
        if (k>0) pos[i]++;
        if (k==0) zero[i]++;
    }

    int minchange = n;
    for(int i=0; i<n-1; ++i) {
        // pos and zero in left and neg and zero in right
        int curr = zero[i] + pos[i] + (n-i-1) - (pos[n-1] - pos[i]);
        //cout << curr << endl;
        minchange = min(minchange, curr);
    }
    fout << minchange << endl;
}
