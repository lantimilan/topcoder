// =========================================================
// 
//       Filename:  prob137D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/15/2011 11:20:50 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/15/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

char buf[600];
int N;
int dp[600][600];
int split[600][600];

int makepal(int numpal, int start)
{
    if (start >= N && numpal>=0) return 0;
    if (numpal<=0) return 600;
    int &ans=dp[numpal][start];
    if (ans>=0) return ans;

    ans=N-start;
    for(int next=start+1; next<=N; ++next) {
        int curr=0;
        for(int p=start,q=next-1; p<q; ++p,--q) {
            if (buf[p]!=buf[q]) curr++;
        }
        curr += makepal(numpal-1, next);
        //printf("curr %d numpal %d start %d next %d\n", curr, numpal, start, next);
        if (curr < ans) {
            ans=curr; split[numpal][start]=next;
        }
    }
    return ans;
}

int main()
{
    gets(buf);
    N=strlen(buf);
    memset(dp,-1,sizeof dp);
    memset(split,-1,sizeof split);

    int k; scanf("%d", &k);

    int ans=makepal(k,0);
    printf("%d\n", ans);

    for(int p=0; p<N; ) {
        int q=split[k--][p]; //printf("%d %d\n", p,q);
        for(int a=p,b=q-1; a<b; ++a,--b) {
            buf[a]=buf[b];
        }
        char ans[500]={0};
        for(int i=p,x=0; i<q; ++i) {
            ans[x++]=buf[i];
        }
        if (p) putchar('+');
        printf("%s", ans);
        p=q;
    }
    printf("\n");
}
