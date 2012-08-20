// =========================================================
// 
//       Filename:  small_equations.cpp
// 
//    Description:  solve up to N<=10
// 
//        Version:  1.0
//        Created:  01/08/2012 11:43:58 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/08/2012, LI YAN
// 
// =========================================================


// Algorithm 1:
// for each factor f of N!
//   x=a*f
//   y=b*(N!/f)
//   for each factor t of N!
//      a=(N!/f)+t
//      b=(N!/t)+f
//
// Algorithm 2:
// ans=0
// for each factor f of (N!)^2 and f<N!
//      ans++;
// ans = ans*2+1    
//
// for each f,t that both divide N!
// x=N! + f*t
// y=N! + (N!/f)*(N!/t)
//
// it is easy to see that both x,y > N!
// since 1/x < 1/N! and 1/y < 1/N!
//
// now the question is, how to count number of factors of (N!)^2 that are <N!
// actually we only need all factors of (N!)^2
//
#include <cstdio>
#include <set>
using namespace std;

int main()
{
    //int N; scanf("%d", &N);
    for(int N=1; N<=10; ++N) {
        int fact=1;
        for(int i=2; i<=N; ++i) fact*=i;
        set<int> xset;
        for(int f=1; f<=fact; ++f) if (fact%f == 0) {
            for(int t=1; t<=fact; ++t) if (fact%t == 0) {
                int a=fact/f+t;
                int b=fact/t+f;
                int x=a*f, y=b*fact/f;

                xset.insert(x);
            }
        }
        long long fact2=(long long)fact*fact;
        int ans2=0;
        for(int f=1; f<fact; ++f) if (fact2 % f==0) {
            ans2++;
        }
        ans2=ans2*2+1;
        printf("N %d N! %d ans %u ans2 %d\n", N, fact, xset.size(), ans2);
    }
}

