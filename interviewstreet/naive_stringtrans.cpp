// =========================================================
// 
//       Filename:  naive_stringtrans.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/07/2012 07:02:23 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/07/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int N, K;
char s[1005];

bool isperiod(const char *str)
{
    for(int p=1; p<N; ++p) if (N%p==0) {
        bool ans=true;
        for(int i=0; i<p; ++i) {
            char ch = str[i];
            for(int j=i; j<N; j+=p) {
                if (str[j]!=ch) { ans=false; goto done; }
            }
        }
        done:
        if (ans) return true;
    }
    return false;
}

void solve()
{
    scanf("%d%d ", &N, &K);   
    gets(s);
    printf("\ntestcase\nN %d K %d\n", N, K); puts(s);
    int ans=0;
    for(int b=0; b<(1<<N); ++b) {
        char s2[1005]={0};
        for(int i=0; i<N; ++i) {
            if (b&1<<i) s2[i]='1';
            else s2[i]='0';
        }
        int diff=0;
        for(int i=0; i<N; ++i)
            if (s[i]!=s2[i]) ++diff;
        if (diff <= K && !isperiod(s2))
            ++ans;
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}
