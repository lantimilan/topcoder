// =========================================================
// 
//       Filename:  CLOSEST.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/07/2012 04:00:02 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/07/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;


const int MAX=50005;
int N, Q;
int X[MAX], Y[MAX], Z[MAX];
int A[MAX], B[MAX], C[MAX];

double sq(double x)
{
    return x*x;
}

void solve()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d%d%d", X+i, Y+i, Z+i);
    scanf("%d", &Q);
    for(int j=0; j<Q; ++j) scanf("%d%d%d", A+j, B+j, C+j);

    // find best for bank[0]
    double dmax=-1;
    int id=-1;
    for(int i=0; i<N; ++i) {
        double dnow = sq(X[i]-A[0]) + sq(Y[i]-B[0]) + sq(Z[i]-C[0]);
        if (dmax<0 || dnow < dmax) {
            id = i; dmax = dnow;
        }
    }
    for(int j=0; j<Q; ++j) printf("%d\n", id);
}

int main()
{
    solve();
}
