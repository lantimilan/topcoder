// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  http://codeforces.ru/contest/113/problem/C
// 
//        Version:  1.0
//        Created:  09/08/2011 09:38:07 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/08/2011, LI YAN
// 
// =========================================================


#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

#define N 300000003

//bitset<N> primes;
vector<bool> primes(N);

void init()
{
    primes[0]=primes[1]=1;
    for(int k=2+2; k<=N; k+=2) primes[k]=1;
    for(int k=3; k*k<=N; k+=2) if (!primes[k])
    for(int j=k*k; j<=N; j+=2*k) primes[j]=1;
}

int main()
{
    init();

    int l,r; cin >> l >> r;
    int ans=0;
    int k;
    // Fermat's Christmas Theorem
    // if p is an odd prime
    // then p=a^2+b^2 iff p mod 4 = 1
    for(k=5; k<l; k+=4)
        ;
    for(; k<=r; k+=4) 
        if (!primes[k]) ++ans;
    if (l<=2&&2<=r) ++ans;
    cout << ans << endl;
}

// vector<bool> is a little slower than bitset<N>
//
// vector<bool> version
// 685010   Sep 9, 2011 9:41:25 AM  lantimilan  C - Double Happiness    GNU C++
// Accepted     4910 ms     38100 KB 
//
// bitset<N> version
// 684998   Sep 9, 2011 9:35:53 AM  lantimilan  C - Double Happiness    GNU C++
// Accepted     4880 ms     38100 KB 
//
// sieve of Eratosthenes
// init array 1 to N to zero (1 means not prime)
// start from 2, pick the first index that remains zero, let it be p
// mark p^2, p^2+2*p, ...
// notice that you can start from p^2 instead of 2*p because earlier ones are
// marked already
// you can do increment of 2*p instead of p because all even number are already
// marked
//
// one way to deal with memory issue is to use bitset<N>
// another way is to use vector<bool>
