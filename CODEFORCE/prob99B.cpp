// =========================================================
// 
//       Filename:  B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/22/2011 08:14:32 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/22/2011, LI YAN
// 
// =========================================================

#include <cstdlib>
#include <iostream>
using namespace std;

void solve()
{
    int n; cin >> n;
    int vol[1005];
    int a,b; a=b=-1;
    for(int i=0; i<n; ++i) {
        cin >> vol[i];
        if (a<0 || vol[a] > vol[i]) a=i;
        if (b<0 || vol[b] < vol[i]) b=i;
    }
    if ((vol[a]+vol[b])%2!=0)
    { cout << "Unrecoverable configuration." << endl;
        return;
    }
    int avg = (vol[a]+vol[b])/2;
    bool good = true;
    for(int i=0; i<n; ++i) if (i!=a&&i!=b)
        if (vol[i]!=avg) { good = false; break; }

    if (good) {
        int diff = abs(vol[a]-vol[b])/2;
        if (diff==0) { cout << "Exemplary pages." << endl; }
        else {
            int from = (vol[a]<vol[b]) ? a : b;
            int to = (vol[a]>vol[b]) ? a : b;
            cout << diff << " ml. from cup #"<< (from+1) << 
                " to cup #" << (to+1) << "." << endl;
        }
    }
    else {
        cout << "Unrecoverable configuration." << endl;
        return;
    }
}
int main()
{
    solve();
}
