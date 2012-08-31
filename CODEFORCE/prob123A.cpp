// =========================================================
// 
//       Filename:  prob123A.cpp
// 
//    Description:  http://codeforces.com/contest/123/problem/A
// 
//        Version:  1.0
//        Created:  11/04/2011 05:45:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 11/04/2011, LI YAN
// 
// =========================================================

// if prime p is such that 2*p > n, then only show up once
// if prime p is such that 2*p <= n, then s[p]==s[2*p]==s[2]
// so we need enough identical char to fill all those 2*p<=n
// and the rest just need any char
//
#include <cstdio>
#include <cstring>
using namespace std;

bool isprime(int n)
{
    if (n<2) return false;
    for(int k=2; k*k<=n; ++k) {
        if (n%k==0) return false;
    }
    return true;
}

int main()
{
    char s[1005]; gets(s);

    int cnt[30]={0};
    int n = (int)strlen(s);
    for(int i=0; i<n; ++i) {
        cnt[s[i]-'a']++;
    }
    int maxcnt=0, maxch=-1;
    for(int i=0; i<26; ++i) {
        if (maxcnt < cnt[i]) { maxcnt=cnt[i]; maxch=i; }
    }

    int mark[1005]={0};
    for(int p=2; 2*p<=n; ++p) if (isprime(p))
    {
        for(int k=p; k<=n; k+=p) mark[k]=1;
    }
    int total=0;
    for(int i=1; i<=n; ++i) total+=mark[i];


    if (maxcnt >= total) {
        puts("YES");
        char sout[1005]={0};
        for(int i=1; i<=n; ++i) if (mark[i]) {
            sout[i-1]=char('a'+maxch);
        }
        cnt[maxch]-=total;
        for(int i=1; i<=n; ++i) if (!mark[i]) {
            int ch;
            for(ch=0; ch<26; ++ch) if (cnt[ch]) break;
            sout[i-1]=char(ch+'a'); cnt[ch]--;
        }
        puts(sout);
    }
    else {
        puts("NO");
    }
}
