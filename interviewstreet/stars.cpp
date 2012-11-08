// =========================================================
// 
//       Filename:  stars.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/07/2012 10:42:44 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 11/07/2012, LI YAN
// 
// =========================================================

// split with one empty subset
// split by using two pts as a line to separate into two regions
// (p1, p2) such that p1 goes into first region and p2 goes into second region
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
using namespace std;

typedef long long int64;
typedef pair<int,int> pii;

int N;
int x[105];
int y[105];
int weight[105];

pii operator+(pii p1, pii p2)
{
    return pii(p1.first + p2.first, p1.second + p2.second);
}
pii operator-(pii p1, pii p2)
{
    return pii(p1.first - p2.first, p1.second - p2.second);
}
// returns true if p3 is on the left of p1-->p2
bool isLeft(pii p1, pii p2, pii p3)
{
    pii sub1, sub2;
    sub1 = p2-p1;
    sub2 = p3-p1;
    int64 x1, y1, x2, y2;
    x1 = sub1.first;
    y1 = sub1.second;
    x2 = sub2.first;
    y2 = sub2.second;
    return x1*y2 - y1*x2 > 0;
}

int main()
{
    scanf("%d", &N);
    int64 sum = 0;
    for (int i=0; i<N; ++i) {
        scanf("%d%d%d", x+i, y+i, weight+i);
        sum += weight[i];
    }
    //printf("sum %lld\n", sum);
    
    int64 diff = abs(sum);
    for (int i=0; i<N; ++i)
    for (int j=0; j<N; ++j) if (i!=j)
    {
        int64 left, right;
        left = weight[i];
        right = weight[j];
        for (int k=0; k<N; ++k) if (k!=i && k!=j) {
            pii p1, p2, p3;
            p1 = pii(x[i], y[i]);
            p2 = pii(x[j], y[j]);
            p3 = pii(x[k], y[k]);
            if (isLeft(p1, p2, p3)) left += weight[k];
            else right += weight[k];
        }
        int64 curr = abs(left - right);
        diff = min(diff, curr);
    }
    printf("%lld\n", (sum - diff)/2);
}

// 
// Name     Language    Time    Status  Result  
// Stars    cpp     2012-11-08 06:58:29     Processed   Accepted
// Score: 96
//  View Details
