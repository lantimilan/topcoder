// =========================================================
// 
//       Filename:  prob117A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2011 08:06:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

struct person_t {
    int start, finish, ti, pos;
};

bool operator<(const person_t &p1, const person_t &p2)
{
    return p1.ti < p2.ti;
}

int main()
{
    int n,m; cin >> n >> m;
    vector<person_t> person(n);
    vector<int> ans(n);

    for(int i=0; i<n; ++i)
    {
        cin >> person[i].start >> person[i].finish >> person[i].ti;
        person[i].pos=i;
        if (person[i].start==person[i].finish) ans[i]=person[i].ti;
    }

    sort(person.begin(), person.end());

    int step=1,x=0;
    for(int i=0, floor=1; i<100000000+10; ++i)
    {
        while(x<n && person[x].ti == i) {
            int pos = person[x].pos;
            int s=person[x].start, f=person[x].finish;
            if (s==f) { ++x; continue; }
            ans[pos]=i;
            if (step>0) {
                if (floor > s) { 
                    ans[pos]+=m-floor+m-s;
                    if (f<=s) ans[pos]+=s-f;
                    else ans[pos]+=s-1+f-1;
                }
                else {
                    ans[pos]+=s-floor;
                    if (f>=s) ans[pos]+=f-s;
                    else ans[pos]+=m-s+m-f;
                }
            }
            else { // step <0
                if (floor >= s) {
                    ans[pos]+=floor-s;
                    if (f<=s) ans[pos]+=s-f;
                    else ans[pos]+=s-1+f-1;
                }
                else {
                    ans[pos]+=floor-1+s-1;
                    if (f>=s) ans[pos]+=f-s;
                    else ans[pos]+=m-s+m-f;
                }
            }
            ++x;
        }
        floor+=step;
        if (floor==m || floor==1) step=-step;
    }
    for(int i=0; i<n; ++i)
        printf("%d\n", ans[i]);
    
}
