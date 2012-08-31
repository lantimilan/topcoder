// =========================================================
// 
//       Filename:  prob138C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/27/2011 04:24:20 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/27/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii, int> pp; // pos, id, pr, id=0 start, =1 mushroom, =2 end, pr=prob or power

vector<pp> obj;
int mushroom[10000+5][105]; // tree prob that affect mushroom[i]

int main()
{
    int n,m; scanf("%d%d", &n, &m);
    for(int i=0; i<n; ++i) {
        int a, h, l, r;
        scanf("%d%d%d%d", &a, &h, &l, &r);
        obj.push_back( pp(pii(a-h,0), l) ); // start at a-h, pr=l/100
        obj.push_back( pp(pii(a-1,2), l) ); // end at a-1, pr=l/100
        obj.push_back( pp(pii(a+1,0), r) ); // start at a+1, pr=r/100
        obj.push_back( pp(pii(a+h,2), r) ); // end at a+h, pr=r/100
    }
    for(int i=0; i<m; ++i) {
        int b,z; scanf("%d%d", &b, &z);  //printf("%d %d\n", b, z);
        obj.push_back( pp(pii(b,1), z) );
    }

    sort(obj.begin(), obj.end());
    double total=0.0;
    int prob[105]={0};
    int power[10000+5]={0};
    int mid=0;
    for(int i=0; i<int(obj.size()); ++i) {
        int pos=obj[i].first.first;
        int id =obj[i].first.second;
        int pr =obj[i].second;

        //printf("pos %d id %d pr %d\n", pos, id, pr);

        if (id==1) { // mushroom
            memcpy(mushroom[mid], prob, sizeof prob);
            power[mid]=pr;
            mid++;
        }
        else if (id==0){ // begin new tree
            prob[pr]++;
        }
        else { // end new tree
            prob[pr]--;
            assert(prob[pr]>=0);
        }
    }
    for(int i=0; i<m; ++i) {
        double curr=power[i];
        for(int p=1; p<=100; ++p) if (mushroom[i][p]){
            curr *= pow(1.0-p/100.0, 1.0*mushroom[i][p]);
        }
        total += curr;
    }
    printf("%lf\n", total);
}

// the algorithm is just to treat each tree as two separate intervals
// sort intervals and mushrooms and keep an array of 1..100 for number of tree
// probability that affects this mushroom. This is necessary as the cumulated
// probability can be very small, close to zero.
//
// 989077   Dec 28, 2011 5:31:10 AM     lantimilan  C - Mushroom Gnomes - 2
// GNU C++  Accepted    330 ms  14800 KB
//
// test 12 is 10^5 trees at 0 and 1 mushroom at 0 with power=1.0, 
// so the answer is 1.0. However, use double to accumulate probability will
// result in very small total probability close to 0.0 and it is not possible to
// recover from there
// 989058   Dec 28, 2011 4:55:53 AM     lantimilan  C - Mushroom Gnomes - 2
// GNU C++  Wrong answer on test 12     140 ms  2100 KB
// 989050   Dec 28, 2011 4:44:23 AM     lantimilan  C - Mushroom Gnomes - 2
// GNU C++  Wrong answer on test 12     160 ms  2100 KB
//
// didn't check l or r being 100 and have some divide-by-zero error
// 989039   Dec 28, 2011 4:36:15 AM     lantimilan  C - Mushroom Gnomes - 2
// GNU C++  Wrong answer on test 5  10 ms   1400 KB 
