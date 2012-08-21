// SRM 552 div1
// p250
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

// documentation
//
// It is easy to see that you need
//N R G B
//
//-------------
//
//1 0 0 0
//
//2 1 1 1
//
//3 2 2 2
//
//4 4 3 3
//
//5 5 5 5
//
//6 7 7 7
//
//Enough pattern, so to make one triangle of N layers you
//need sum of 1 to N balls, which is N(N+1)/2. For N=3k or
//3k+2 this number is a multiple of 3 so you need the same
//number of three colors, and the answer is simply B/(S/3),
//where R>=G>=B and S = N(N+1)/2.
//
//The tricky case is N=3k+1, then S = 3k' + 1. Now you need
//to distribute balls to make max number of triangles. Let
//us image that the optimal answer is m triangles, then you
//need at least m*((S-1)/3) for each color, and whatever
//remain can be any color, as long as the remaining balls
//are at least m. So the answer is min of (R+G+B)/S and
//B/(S/3). The special case is N=1, where you return R+G+B.
//An easier way to visualize this is that you grow three
//equal columns for each color, then what has been cut off
//from each color are the remaining balls you have, those
//balls are equivalent and can be distributed to any
//triangle you want to make.
//
//The problem setter is more evil than this to introduce a
//few integer overflow even for long long, if you use *
//instead of /
