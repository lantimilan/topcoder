// =========================================================
// 
//       Filename:  prob118B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/07/2011 09:50:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/07/2011, LI YAN
// 
// =========================================================

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n; cin >> n;

    for(int k=n; k>=-n; --k)
    {
        int kk=abs(k);
        string space(2*kk,' ');
        cout << space;
        int m=n-kk;
        for(int j=m; j>=-m; --j) {
            if (j!=m) cout << ' ';
            cout << m-abs(j);
        }
        cout << endl;
    }
}
