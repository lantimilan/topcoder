#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define sz(a) int(a.size())

template<class T>
T min3(T a, T b, T c)
{
    return min(a, min(b,c));
}

class FoxPaintingBalls
{ 
public: 
    long long theMax(long long R, long long G, long long B, int N) 
    { 
        long long a[3] = {R, G, B};
        sort(a, a+3);
        long long b[3];
        b[0] = b[1] = b[2] = (long long)(N+1) * N/2/3;
        if (b[1] == 0) return a[0]+a[1]+a[2];

        if (N%3 != 1) return a[0]/b[0];

        assert(N%3 == 1);
        b[2]++;
        
        long long asum = a[0]+a[1]+a[2];
        long long bsum = b[0]+b[1]+b[2];
        /*
        long long lo=0, hi = asum+1;
        while(lo+1 < hi) {
            long long m = lo+hi >> 1;
            // need b[0]*m for a[0], a[1], a[2]
            // and asum has at least m after subtract bsum*m
            if (a[0]/m < b[0] || asum/m < bsum) hi=m;
            else lo=m;
        }
        return lo;
        */
        return min(asum/bsum, a[0]/b[0]);
    } 
    
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
