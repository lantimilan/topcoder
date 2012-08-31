// =========================================================
// 
//       Filename:  gendata.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/14/2011 10:36:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/14/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int main()
{
    int n=5000;
    cout << n << endl;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<=i; ++j) cout << 0;
        for(int j=i+1; j<n; ++j) cout << 1;
        cout << endl;
    }
}
