// =========================================================
// 
//       Filename:  prob135D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/22/2011 09:25:12 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/22/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

int nrow, ncol;
char table[1005][1005];
int lpos[1005], rpos[1005]; // for row[0] and row[n-1], lpos[i] is rightmost consecutive '1'
// for row[1] to row[n-2], lpos[i] is leftmost '1' from inner left, rpos[i] is
// rightmost '1' from inner right

int main()
{
    scanf("%d%d", &nrow, &ncol); gets(table[0]); // eat trailing newline
    for(int i=0; i<nrow; ++i) {
        gets(table[i]);
        puts(table[i]);
    }

    int row=0;
    for(int j=0, jj; j<ncol; ++j) {
        for(jj=max(j,jj); jj<ncol && table[row][jj]=='1'; ++jj)
            ;
        lpos[j]=jj-1;
    }
    row=nrow-1;
    for(int j=0, jj; j<ncol; ++j) {
        for(jj=max(j,jj); jj<ncol && table[row][jj]=='1'; ++jj)
            ;
        lpos[j]=jj-1;
    }

    for(row=1; row<nrow-1; ++row) {
        int left=0, right=ncol-1;
        while(left<right) {
            if (table[row][left]=='1') left++;
            if (table[row][right]=='1') right--;
        }
        if (left >= right) // all 
    }

}
