// =========================================================
// 
//       Filename:  probB.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/23/2011 08:32:59 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/23/2011, LI YAN
// 
// =========================================================

#include <iomanip>
#include <iostream>
using namespace std;


int main()
{
    int n,m,h; cin >> n >> m >> h; h--;
    int s[1005]={0};
    int sum=0;
    for(int i=0; i<m; ++i) { cin >> s[i]; sum+=s[i]; }

    if (sum < n) { cout << fixed << setprecision(10) << -1.0 << endl; return 0; }

    double ans=1.0;
    for(int i=1; i<n; ++i)
    {
        ans*= (sum-s[h]-i+1)/(double)(sum-i);
    }
    cout << fixed << setprecision(10) << (1.0-ans) << endl;
}
