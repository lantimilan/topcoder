// =========================================================
// 
//       Filename:  luckystr.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/20/2012 09:21:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/20/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool issubstr(const string &text, const string &sub)
{
    for(int i=0; i<int(text.length()); ++i)
    {
        int j;
        for(j=0; j<int(sub.length()); ++j)
        {
            if (i+j<int(text.length()) && text[i+j]==sub[j]) {}
            else break;
        }
        if (j>=int(sub.length())) return true;
    }
    return false;
}

int main()
{
    int K, N; cin >> K >> N;
    vector<string> lucky(K);
    for(int i=0; i<K; ++i) cin >> lucky[i];
    for(int i=0; i<N; ++i) {
        bool good=false;
        string text; cin >> text;
        if (int(text.length()) >= 47) good=true;
        for(int j=0; j<K; ++j) if (issubstr(text, lucky[j])) good=true;

        if (good) cout << "Good" << endl;
        else cout << "Bad" << endl;
    }
}
