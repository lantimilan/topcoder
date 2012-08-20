// =========================================================
// 
//       Filename:  GRAYSC.cpp
// 
//    Description:  if n>=(64+1)*2, then there has to be two pairs with same
//    value, because a[i]^a[i+1] has only 1 bit that is 1
//    when n is small, brute force all (n choose 3) and look for the 4th
// 
//        Version:  1.0
//        Created:  07/01/2012 05:25:28 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <set>
#include <map>
using namespace std;

typedef unsigned long long uint64;

multiset<uint64> st;
uint64 a[100000+5];

int main()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%llu", a+i); 
        st.insert(a[i]);
    }
    if (N>200) { puts("Yes"); }
    else {
        uint64 v[4];
        for(int i1=0; i1<N; ++i1)
        for(int i2=i1+1; i2<N; ++i2)
        for(int i3=i2+1; i3<N; ++i3)
        {
            v[0]=a[i1]; v[1]=a[i2]; v[2]=a[i3];
            v[3]=v[0]^v[1]^v[2];
            multiset<uint64> st2;
            for(int x=0; x<4; ++x) { 
                st2.insert(v[x]);
            }
            bool good=true;
            for(int x=0; x<4; ++x) {
                if (st.count(v[x]) < st2.count(v[x]))
                    good=false;
            }
            if (good) { puts("Yes"); return 0; }
        }
        puts("No");
    }
}
