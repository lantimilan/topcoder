// =========================================================
// 
//       Filename:  unluckynumbers.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/16/2012 09:07:22 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

int N;
int64 K;

template<class T>
T gcd(T a, T b)
{
    return b==0?a:gcd(b,a%b);
}

template<class T>
T lcm(T a, T b)
{
    T g = gcd(a,b);
    return a/g*b;
}

int main()
{
    scanf("%d%lld", &N, &K);
    int64 ll, gg, a, g;
    ll=1; gg=K;
    for(int i=0; i<N; ++i) {
        scanf("%lld", &a);
        a/=gcd(a,ll);
        g = gcd(gg,a);
        ll *= g;
        gg /= g;
        printf("gg %lld ll %lld\n", gg, ll);
    }
    int ans=0;
    for(int64 i=1; i*i<=gg; ++i) {
        if (gg % i == 0) { ans++;
            if (i*i!=gg) ans++;
        }
    }
    printf("%d\n", ans-1);
}


// seems you need mu function for this problem
