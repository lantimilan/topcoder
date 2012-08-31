// =========================================================
// 
//       Filename:  prob187A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/10/2012 09:07:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/10/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

int a[200000+5];
int b[200000+5];
int rev[200000+5];
int arev[200000+5];
int N;

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) { scanf("%d", &a[i]); --a[i]; }
    for(int i=0; i<N; ++i) { scanf("%d", &b[i]); --b[i]; }

    for(int i=0; i<N; ++i) rev[b[i]]=i;
    for(int i=0; i<N; ++i) arev[i] = rev[a[i]];
    for(int i=0; i<N; ++i) a[i] = arev[i];

    //for(int i=0; i<N; ++i) printf("%d ", a[i]); putchar('\n');
    int ans=N-1;
    for(int p=1; p<N; ++p) {
        if (a[p]>a[p-1]) ans--;
        else break;
    }

    printf("%d\n", ans);
}

// 1682126  May 11, 2012 9:35:28 PM     lantimilan  A - Permutations    GNU C++
// Accepted     160 ms  4500 KB 
//
// The only observation is that the increasing prefix need not to be moved,
// other numbers need exactly one move
