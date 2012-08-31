// =========================================================
// 
//       Filename:  prob118A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/07/2011 10:00:21 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/07/2011, LI YAN
// 
// =========================================================

#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int find(string s, char ch)
{
    for(int i=0; i<int(s.size()); ++i)
        if (s[i]==ch) return i;
    return -1;
}
int main()
{
    string in, out;
    cin >> in;

    for(int i=0; i<int(in.size()); ++i)
    {
        string vowel="AEIOUY";
        if (find(vowel,toupper(in[i]))>=0) {
            // vowel, skip
        }
        else {
            out += '.';
            out += tolower(in[i]);
        }
    }
    cout << out << endl;
}

// 749806   Oct 8, 2011 9:01:33 AM  lantimilan  A - String Task     GNU C++
// Accepted     30 ms   1400 KB 
