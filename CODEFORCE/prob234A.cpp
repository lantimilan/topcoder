// =========================================================
// 
//       Filename:  prob234A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 02:12:05 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

// only constraint is on the two students in the same desk
// id1 != id2 +-1
// if one L and one R, have to be L R
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    int n; fin >> n;
    string s; fin >> s;
    for(int i=0; i<n/2; ++i) {
        int j = i+n/2;
        if (s[i] == 'R' && s[j] == 'L')
            fout << j+1 << ' ' << i+1 << endl;
        else
            fout << i+1 << ' ' << j+1 << endl;
    }
}
