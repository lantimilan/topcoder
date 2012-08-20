// =========================================================
// 
//       Filename:  substringdiff.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/30/2011 08:55:22 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/30/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

char P[1505], Q[1505];

void solve()
{
    int K; scanf("%d", &K);
    scanf("%s%s", P, Q);

    int N=strlen(P);    

    int lo, hi;
    lo=K; hi=N;
    while(lo < hi) {
        int L=(lo+hi+1)/2;
        bool good = false;
        // match P[0] to each of Q[0]..Q[N-1]
        for(int i=0; i+L<=N; ++i)
        {
            int diff = 0;
            for(int k=0; k<L; ++k)
                if (P[k]!=Q[i+k]) diff++;
            if (diff <= K) { good=true; goto done; }
            for(int ii=1, jj=i+1; ii+L<=N && jj+L<=N; ++ii, ++jj)
            {
                if (P[ii-1]!=Q[jj-1]) --diff;
                if (P[ii+L-1] != Q[jj+L-1]) ++diff;
                if (diff <= K) { good = true; goto done; }
            }            
        }
        // match Q[0] to each of P[0]..P[N-1]
        for(int i=0; i+L<=N; ++i)
        {
            int diff = 0;
            for(int k=0; k<L; ++k)
                if (P[i+k]!=Q[k]) diff++;
            if (diff <= K) { good=true; goto done; }
            for(int ii=i+1, jj=1; ii+L<=N && jj+L<=N; ++ii, ++jj)
            {
                if (P[ii-1]!=Q[jj-1]) --diff;
                if (P[ii+L-1] != Q[jj+L-1]) ++diff;
                if (diff <= K) { good = true; goto done; }
            }            
        }
        done:
        if (good) {
            lo=L;
        }
        else {
            hi=L-1;
        }
    }

    //printf("L %d A %d B %d\n", L, A, B);
    //char ans[1005]={0};
    //if (L) strncpy(ans, P+A, L);
    //puts(ans);
    printf("%d\n", lo);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
