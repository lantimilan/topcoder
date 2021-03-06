// =========================================================
// 
//       Filename:  sol95D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2011 02:09:47 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2011, LI YAN
// 
// =========================================================
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1000+20;
const int mod=1000000007;

int f[maxn][maxn];
char L[maxn],R[maxn];
int test,dist;

void renew(int &a,int b)
{
        a+=b;
        if (a>=mod) a-=mod;
}

int calc(char st[],bool flag)
{
        int n=strlen(st+1);
        int res=0;
        for (int i=1;i<n;i++)
        for (int j=1;j<10;j++)
        if (j==4 || j==7) renew(res,f[i-1][1]);
        else renew(res,f[i-1][dist+1]);

        int state=dist+1;
        for (int i=1;i<=n;i++)
        {
                int digit=st[i]-'0';
                for (int j=(i>1?0:1);j<digit;j++)
                if (state==0) renew(res,f[n-i][0]);else
                if (j==4 || j==7)
                {
                        if (state<=dist) renew(res,f[n-i][0]);
                        else renew(res,f[n-i][1]);
                } else
                {
                        if (state+1<=dist) renew(res,f[n-i][state+1]);
                        else renew(res,f[n-i][dist+1]);
                }

                if (state==0) state=0;else
                if (digit==4 || digit==7)
                {
                        if (state<=dist) state=0;
                        else state=1;
                } else state=min(state+1,dist+1);
        }
        if (flag) renew(res,state==0);
        return res;
}

int main()
{
        scanf("%d%d",&test,&dist);

        f[0][0]=1;
        for (int i=1;i<=1005;i++)
        for (int j=0;j<=dist+1;j++)
        for (int k=0;k<10;k++)
        if (j==0) renew(f[i][j],f[i-1][j]);else
        if (k==4 || k==7)
        {
                if (j<=dist) renew(f[i][j],f[i-1][0]);
                else renew(f[i][j],f[i-1][1]);
        } else
        {
                if (j+1<=dist) renew(f[i][j],f[i-1][j+1]);
                else renew(f[i][j],f[i-1][dist+1]);
        }

        for (;test--;)
        {
                scanf("%s%s",L+1,R+1);
                int A=calc(R,1);
                int B=calc(L,0);
                A-=B;
                if (A<0) A+=mod;
                printf("%d\n",A);
        }
}
