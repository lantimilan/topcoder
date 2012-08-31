// =========================================================
// 
//       Filename:  prob148D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/05/2012 09:38:43 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/05/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

double win[2][1005][1005];

double calc(int w, int b, int turn)
{
    double &ans=win[turn][w][b];
    if (w+b==0) {
        if (turn == 0) return ans=0.0;
        else return ans=1.0;
    }

    if (ans>=0) return ans;
    if (turn == 0) {
        ans = (double)w/(w+b);
        if (b>0) ans += (double)b/(w+b)*(1.0-calc(w,b-1,1-turn));
    }
    else {
        if (w==0) ans=1.0;
        else {
            ans = (double)w/(w+b);
            // one remain mouse jumps off
            if (b>0) {
                double p=(double)b/(w+b);
                double p1=(double)w/(w+b-1);
                double p2=(double)(b-1)/(w+b-1);
                // w, b-1
                if (w>0) ans += p*p1*(1.0-calc(w-1,b-1,1-turn));
                if (b-1>0) ans += p*p2*(1.0-calc(w,b-2,1-turn));
            }
        }
    }
    //printf("w %d b %d turn %d ans %f\n", w, b, turn, ans);
    return ans;
}

int main()
{
    int w, b; scanf("%d%d", &w, &b);
    for(int turn=0; turn < 2; ++turn)
    for(int w=0; w<=1000; ++w)
    for(int b=0; b<=1000; ++b)
        win[turn][w][b]=-1.0;

    double ans = calc(w, b, 0);
    printf("%.10f\n", ans);
}
