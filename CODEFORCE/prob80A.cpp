// =========================================================
// 
//       Filename:  prob69A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  04/19/2011 11:37:07 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/19/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

int cnt;
int primes[100];
void init()
{
    cnt=0;
    int isprime[100]; for(int i=0; i<100; ++i) isprime[i] = 1;
    for(int k=2; k<100; k++) if (isprime[k])
    { for(int p=k+k; p<100; p+=k) isprime[p] = 0; }
    for(int p=2; p<100; ++p) if (isprime[p]) primes[cnt++] = p;
}

void solve()
{
    int a, b; cin >> a >> b;
    int i;
    for(i=0; i<cnt; ++i) if (primes[i] == a) break;
    assert(i+1<cnt);
    string yes="YES", no="NO";
    if (b==primes[i+1]) cout << yes << endl;
    else cout << no << endl;
}

int main()
{
    init();
    solve();
}
