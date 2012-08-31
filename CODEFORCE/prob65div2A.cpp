// =========================================================
// 
//       Filename:  prob65div2A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  03/29/2011 09:51:18 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/29/2011, LI YAN
// 
// =========================================================
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void solve()
{
    int n; cin >> n;
    for(int i=0; i<n; ++i)
    {
        string word; cin >> word;
        int k = word.length();
        if (k > 10)
        {
            ostringstream ss; ss << (k-2);
            word = word[0] + ss.str() + word[k-1];
        }
        cout << word << endl;
    }
}
int main()
{
    solve();
}
