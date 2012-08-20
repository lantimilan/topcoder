// =========================================================
// 
//       Filename:  LUKYDRIV.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/LUKYDRIV
// 
//        Version:  1.0
//        Created:  08/01/2012 09:15:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/01/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

// #subseq is the same if we permute input into
// a monotonic sequene
//
typedef long long int64;
const int MOD = 1000000000+7;
char line[10000+5];

void refadd(int &a, int b)
{
    a = ((int64)a+b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a*b % MOD;
}

int choose(int n, int r)
{
    if (n<r) return 0;
    assert(r<=4);
    int64 ans=1;
    for(int i=0; i<r; ++i)
        ans *= (n-i);
    for(int i=1; i<=r; ++i)
        ans /= i;
    return ans % MOD;
}


int main()
{
    int T; scanf("%d ", &T);
    while(T--) {
        scanf("%s", line); 
        int ans=0;
        int n = strlen(line);
        int cnt[10] = {0};
        for(int i=0; i<n; ++i)
            cnt[line[i]-'0']++;

        for(int l=1, upp=10; l<=4; ++l, upp*=10) {
            int d[10] = {0};
            for(int i=1; i<upp; ++i) {
                int cur = i;
                int sum = 0;
                for(int p=0; p<l; ++p) {
                    d[p] = cur % 10; sum += d[p];
                    cur /= 10;
                }
                if (sum % 9) continue;
                bool mono = true;
                for(int p=0; p<l-1; ++p)
                    if (d[p] > d[p+1]) mono = false;
                if (mono) {
                    int use[10] = {0};
                    for(int p=0; p<l; ++p)
                        use[d[p]]++;
                    int tmp=1;
                    for(int x=0; x<10; ++x)
                        tmp = mult(tmp, choose(cnt[x], use[x]));
                    refadd(ans, tmp);
                }
            }

        }
        printf("%d\n", ans);
    }
}

// Accepted
