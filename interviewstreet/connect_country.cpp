// =========================================================
// 
//       Filename:  connect_country.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/08/2012 10:00:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/08/2012, LI YAN
// 
// =========================================================

// do not see a DP solution, would simulation work?
// simu.cpp has the simulation code
//
#include <cstdio>
using namespace std;

const int sol[] = {
0,
0,
1,
2,
3,
4,
6,
7,
9,
10,
12,
14,
16,
18,
20,
22,
24,
26,
28,
30,
32,
34,
37,
39,
41,
44,
46,
48,
51,
53,
55,
};

int main()
{
    int N; scanf("%d", &N);
    printf("%d\n", sol[N]);
}

// my goodness, you can get AC with that
//
// Connect the country  cpp     2012-02-26 06:25:28     Processed   Accepted
// Score: 20
//  View Details
