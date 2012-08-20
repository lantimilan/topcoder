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

// formula
// observe that if all queen in same color(B/W), then they cannot attach each
// other with a knight move, but queens cannot stay in the same color in general as they do attack diagonally
//
// algorithm from wikipedia
// This heuristic solves N queens for any N ≥ 4. It forms the list of numbers for vertical positions (rows) of queens with horizontal position (column) simply increasing. N is 8 for eight queens puzzle.

//    If the remainder from dividing N by 6 is not 2 or 3 then the list is simply all even numbers followed by all odd numbers ≤ N
//    Otherwise, write separate lists of even and odd numbers (i.e. 2,4,6,8 - 1,3,5,7)
//    If the remainder is 2, swap 1 and 3 in odd list and move 5 to the end (i.e. 3,1,7,5)
//    If the remainder is 3, move 2 to the end of even list and 1,3 to the end of odd list (i.e. 4,6,8,2 - 5,7,9,1,3)
//    Append odd list to the even list and place queens in the rows given by these numbers, from left to right (i.e. a2, b4, c6, d8, e3, f1, g7, h5)


#include <cassert>
#include <iostream>
using namespace std;

int conf[10000+5];

bool attacked(int i, int j)
{
    for(int r=0; r<i; ++r) {
        if (conf[r] == j) return true;
        if (i+j == r+conf[r]) return true;
        if (i-j == r-conf[r]) return true;
    }

    // check knight move
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
    int k=0;
    for(int i=2; i<=N; i+=2) conf[k++]=i;
    for(int i=1; i<=N; i+=2) conf[k++]=i;
    if (N%6 == 2) {
        assert(conf[N/2]==1 && conf[N/2+1]==3 && conf[N/2+2]==5);
        swap(conf[N/2], conf[N/2+1]);
        for(int i=N/2+2; i<N-1; ++i) conf[i] = conf[i+1];
        conf[N-1]=5;
    }
    else if (N%6 == 3) {
        for(int i=0; i<N/2-1; ++i) conf[i] = conf[i+1];
        conf[N/2-1] = 2;
        for(int i=N/2; i+2<N; ++i) conf[i] = conf[i+2];
        conf[N-2]=1; conf[N-1]=3;
    }
    else { // nothing to do
    }

    bool good=true;
    for(int i=0; i<N; ++i) {
        if (attacked(i,conf[i])) good = false;
    }
    cout << "good=" << boolalpha << good << endl;
    for(int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << conf[i];
    }
    cout << endl;
}
