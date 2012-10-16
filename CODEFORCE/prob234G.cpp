// =========================================================
// 
//       Filename:  prob234G.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 01:53:54 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n; fin >> n;
    fout << n-1 << "\n";
    for(int i=1; i<n; ++i) {
        fout << i;
        for(int j=1; j<=i; ++j) {
            fout << " " << j;
        }
        fout << "\n";
    }
}
