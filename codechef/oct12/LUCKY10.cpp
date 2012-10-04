// =========================================================
// 
//       Filename:  LUCKY10.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/04/2012 11:09:05 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/04/2012, LI YAN
// 
// =========================================================

// use 7 to kill 6, 5, 3, 2, 1, 0, 4, 7
// use 4 to kill 3, 2, 1, 0, 4

#include <cstdio>
#include <cstring>
using namespace std;

int doseven(int from[], int to[])
{
    const int K = 7;
    int seq[] = {6, 5, 3, 2, 1, 0, 4, 7};
    int ans;
    int size = sizeof(seq) / sizeof(seq[0]);
    ans = 0;
    for(int i=0; i<size; ++i) {
        if (to[seq[i]] >= from[K]) {
            ans += from[K];
            to[seq[i]] -= from[K];
            from[K] = 0;
            break;
        } else {
            int val = to[seq[i]];
            ans += val;
            from[K] -= val;
            to[seq[i]] = 0;
        }
    }
    return ans;
}

int dofour(int from[], int to[])
{
    const int K = 4;
    int seq[] = {3, 2, 1, 0, 4};
    int ans;
    int size = sizeof(seq) / sizeof(seq[0]);
    ans = 0;
    for(int i=0; i<size; ++i) {
        if (to[seq[i]] >= from[K]) {
            ans += from[K];
            to[seq[i]] -= from[K];
            from[K] = 0;
            break;
        } else {
            int val = to[seq[i]];
            ans += val;
            from[K] -= val;
            to[seq[i]] = 0;
        }
    }
    return ans;
}

int main()
{
    int T; scanf("%d ", &T);
    while(T--) {
    char line[20000+5];
    int A[10] = {0};
    int B[10] = {0};

    int n;
    gets(line);
    n = strlen(line);
    for(int i=0; i<n; ++i)
        A[line[i]-'0']++;

    gets(line);
    n = strlen(line);
    for(int i=0; i<n; ++i)
        B[line[i]-'0']++;
    
    int seven, four;
    seven = four = 0;
    seven += doseven(A, B);
    seven += doseven(B, A);
    four  += dofour(A, B);
    four  += dofour(B, A);

    char ans[20000+5];
    for(int i=0; i<seven; ++i)
        ans[i] = '7';
    for(int i=0; i<four; ++i)
        ans[i+seven] = '4';
    ans[seven + four] = '\0';
    puts(ans);
    }
}


// Correct Answer
// Execution Time: 0.23
