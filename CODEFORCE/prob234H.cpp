// =========================================================
// 
//       Filename:  prob234H.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 10:04:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

// start with 0 or 1, then merge blocks
//
#include <fstream>
#include <iostream>
using namespace std;

int first[100000+5];
int second[100000+5];
int merge[2][200000+5];
int result[2][200000+5];
int block[2];

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m; fin >> n;
    for(int i=0; i<n; ++i)
        fin >> first[i];
    fin >> m;
    for(int i=0; i<m; ++i)
        fin >> second[i];
    
    int i, j;
    int s;
    for(s=0; s<2; ++s) {
        int b = s;
        int len = 0;
        for(i=j=0; i<n || j<m; b=1-b, block[s]++) {
            while(i<n && first[i] == b) {
                result[s][len] = b;
                merge[s][len++] = i++;
            }
            while(j<m && second[j] == b) {
                result[s][len] = b;
                merge[s][len++] = n+j;
                j++;
            }
        }
        if (result[s][len-1] == 0) block[s]--;
    }
    if (block[0] < block[1]) s=0;
    else s=1;

    for(int i=0; i<n+m; ++i) {
        if (i) fout << ' ';
        fout << merge[s][i]+1;
    }
    fout << endl;
    int ans = block[s];
    fout << ans << endl;
    bool begin = true;
    for(int i=0, b=result[s][0]; i<n+m; b=1-b) {
        for(; i<n+m && result[s][i] == b; ++i)
            ;
        if (!begin) fout << ' ';
        if (i>=n+m && result[s][n+m-1] == 0) { /* skip last flip if already zero*/}
        else { fout << i; }
        begin = false;
    }
    fout << endl;
}

// Accepted
//
// this code is very error-prone, how to write it better?
