// =========================================================
// 
//       Filename:  prob110D.cpp
// 
//    Description:  http://codeforces.com/contest/110/problem/D
// 
//        Version:  1.0
//        Created:  09/15/2011 10:25:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int lucky[2000];
    int cnt=0;
    lucky[cnt++]=0;
    for(int d=1; d<=9; ++d)
    for(int b=0; b<(1<<d); ++b)
    {
        int elem=0;
        for(int i=d-1; i>=0; --i)
        {
            elem = elem*10 + ((b&1<<i)?7:4);
        }
        lucky[cnt++]=elem;
    }
    lucky[cnt++]=1<<30;
    //for(int i=0; i<20; ++i) cout << lucky[i] << ' '; cout << endl;
    //cout << cnt << endl;

    int p[2],v[2],k; cin >> p[0] >> p[1] >> v[0] >> v[1] >> k;
    long long sum=0LL;
    for(int a=1,b=k; a<cnt-1&&b<cnt-1; ++a,++b)
    {
        int x[2],y[2],s[2],t[2],d[2];
        int xx[2],yy[2];
        x[0]=max(p[0],lucky[a-1]+1);
        x[1]=min(p[1],lucky[a]);
        y[0]=max(v[0],lucky[b]);
        y[1]=min(v[1],lucky[b+1]-1);
        d[0]=x[1]-x[0]+1;
        d[1]=y[1]-y[0]+1;
        if (d[0]>0 && d[1]>0) sum += (long long)d[0]*d[1];
        s[0]=max(v[0],lucky[a-1]+1);
        s[1]=min(v[1],lucky[a]);
        t[0]=max(p[0],lucky[b]);
        t[1]=min(p[1],lucky[b+1]-1);
        d[0]=s[1]-s[0]+1;
        d[1]=t[1]-t[0]+1;
        if (d[0]>0 && d[1]>0) sum += (long long)d[0]*d[1];

        // the only time when we have an overlap is
        // k=1 and both p[] and v[] cover lucky[index]
        // since we need the intersection of p[] with low
        // and p[] with high, and the intersection of v[] with 
        // low and v[] with high
        /*
        xx[0]=max(x[0],t[0]);
        xx[1]=min(x[1],t[1]);
        yy[0]=max(y[0],s[0]);
        yy[1]=min(y[1],s[1]);
        d[0]=xx[1]-xx[0]+1;
        d[1]=yy[1]-yy[0]+1;
        if (d[0]>0 && d[1]>0) sum -= (long long)d[0]*d[1];
        */
        if (k==1 && p[0]<=lucky[a] && lucky[a]<=p[1] &&
            v[0]<=lucky[a] && lucky[a]<=v[1])
            {
                sum--;
            }

    }
    double ans = sum/(1.0*(p[1]-p[0]+1)*(v[1]-v[0]+1));
    printf("%.10lf\n", ans);
}

// Doing this a second time, run into more issues
//
// The tricky case is 47 47 47 47 1, which is case 51
//
// 704180   Sep 16, 2011 11:04:22 AM    lantimilan  D - Lucky Probability   GNU
// C++  Accepted    30 ms   1400 KB
// 704119   Sep 16, 2011 10:21:01 AM    lantimilan  D - Lucky Probability   GNU
// C++  Wrong answer on test 1  10 ms   1400 KB
// 704099   Sep 16, 2011 10:09:16 AM    lantimilan  D - Lucky Probability   GNU
// C++  Wrong answer on test 51     30 ms   1400 KB
// 704086   Sep 16, 2011 10:02:01 AM    lantimilan  D - Lucky Probability   GNU
// C++  Wrong answer on test 3  10 ms   1400 KB
// 704050   Sep 16, 2011 9:44:40 AM     lantimilan  D - Lucky Probability   GNU
// C++  Wrong answer on test 3  30 ms   1400 KB 
