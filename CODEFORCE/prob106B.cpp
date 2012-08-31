// =========================================================
// 
//       Filename:  prob106B.cpp
// 
//    Description:  http://codeforces.com/contest/106/problem/B
// 
//        Version:  1.0
//        Created:  09/13/2011 08:39:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/13/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <vector>
using namespace std;

struct laptop_t
{
    int speed, ram, hdd, cost, id;
};

int main()
{
    int n; scanf("%d",&n);
    laptop_t m;
    vector<laptop_t> mvec(n);
    vector<laptop_t> goodvec;
    for(int i=0; i<n; ++i)
    {
        scanf("%d%d%d%d", &m.speed, &m.ram, &m.hdd, &m.cost);
        m.id=i;
        mvec[i]=m;
    }

    for(int i=0; i<n; ++i)
    {
        bool outdated=false;
        for(int j=0; j<n; ++j) if (i!=j)
        {
            if (mvec[j].speed > mvec[i].speed &&
                mvec[j].ram > mvec[i].ram &&
                mvec[j].hdd > mvec[i].hdd)
            { outdated=true; break; }
        }
        if (!outdated) { goodvec.push_back(mvec[i]); }
    }
    int price=goodvec[0].cost, id=goodvec[0].id;
    for(int i=1; i<int(goodvec.size()); ++i)
    {
        if (goodvec[i].cost < price)
        { price=goodvec[i].cost; id=goodvec[i].id; }
    }
    printf("%d\n",(id+1));
}
