// http://codeforces.com/contest/109/problem/B
//
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

vector<int> lucky;

const int INF=1<<30;

void init()
{
    lucky.push_back(0);
    for(int l=1; l<=9; ++l)
    for(int b=0; b<(1<<l); ++b)
    {
        int k=0;
        for(int i=0,f=1; i<l; ++i,f*=10)
        {
            if (b&1<<i) k+=f*7;
            else k+=f*4;
        }
        lucky.push_back(k);
    }
    lucky.push_back(INF);

    //for(int i=0; i<20; ++i) cout << lucky[i] << ' '; cout << endl;
}

int main()
{
    int p[2], v[2], k;
    init();
    //cin >> p[0] >> p[1] >> v[0] >> v[1] >> k;
    scanf("%d%d%d%d%d",&p[0],&p[1],&v[0],&v[1],&k);

    long long sum=0;
    int n=int(lucky.size())-1;
    for(int a=1,b=k; b<n; ++a,++b)
    {
        int x[2],y[2],d[2];
        x[0]=max(p[0],lucky[a-1]+1);
        x[1]=min(p[1],lucky[a]);
        y[0]=max(v[0],lucky[b]);
        y[1]=min(v[1],lucky[b+1]-1);
        //cout << x[0] << ' ' << x[1] << ' ' << y[0] << ' ' << y[1] << endl;
        d[0]=x[1]-x[0]+1; d[1]=y[1]-y[0]+1;
        if (d[0]>0 && d[1]>0) sum += (long long)d[0]*d[1];

        int s[2],t[2];
        s[0]=max(v[0],lucky[a-1]+1);
        s[1]=min(v[1],lucky[a]);
        t[0]=max(p[0],lucky[b]);
        t[1]=min(p[1],lucky[b+1]-1);
        d[0]=s[1]-s[0]+1; d[1]=t[1]-t[0]+1;
        if (d[0]>0 && d[1]>0) sum += (long long)d[0]*d[1];

        int xx[2],yy[2];
        xx[0]=max(x[0],t[0]);
        xx[1]=min(x[1],t[1]);
        yy[0]=max(y[0],s[0]);
        yy[1]=min(y[1],s[1]);
        d[0]=xx[1]-xx[0]+1; d[1]=yy[1]-yy[0]+1;
        if (d[0]>0 && d[1]>0) sum -= (long long)d[0]*d[1];
    }
    double ans = sum/(1.0*(p[1]-p[0]+1)*(v[1]-v[0]+1));
    printf("%.10lf\n",ans);
}

// Algorithm:
// since there are only 2+2^2+...+2^9=1023 different lucky numbers <= 10^9
// we can try all slide window start from lucky[1]=4 to lucky[last]=777777777
//
// for each interval of lucky[i] to lucky[i+k-1], we can accomodate pairs
// with lucky[i-1] < lo <= lucky[i] and lucky[i+k-1] <= hi < lucky[i+k]
//
// now we can try both p[2] as lo, v[2] as hi, or p[2] as hi and v[2] as lo
// notice that counts in different slide window will not overlap, since they
// fall into different lucky[] intervals.
// 
// there is a potential catch that the two counts at the same lucky[] interval
// might have overlap, that is the code subtracting them
//

// 689103   Sep 11, 2011 9:22:45 AM     lantimilan  B - Lucky Probability   GNU C++     Accepted    30 ms   1400 KB
// 
// WA because forgot to subtract overlap pairs
// 689097  Sep 11, 2011 9:11:16 AM     lantimilan  B - Lucky Probability   GNU C++     Wrong answer on test 51     30 ms   1400 KB 
