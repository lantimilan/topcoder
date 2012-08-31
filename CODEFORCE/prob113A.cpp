// =========================================================
// 
//       Filename:  prob113A.cpp
// 
//    Description:  http://codeforces.ru/contest/113/problem/A
// 
//        Version:  1.0
//        Created:  09/08/2011 10:36:40 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/08/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define sz(a) int(a.size())

int main()
{
    string words[3][2];
    words[0][0]="lios"; words[0][1]="liala";
    words[1][0]="etr";  words[1][1]="etra";
    words[2][0]="initis"; words[2][1]="inites";

    vector<string> vec;
    vector<int> types, genders;

    string text;
    while(cin >> text) vec.push_back(text);

    // check all words valid
    bool good=false;
    for(size_t k=0; k<vec.size(); ++k)
    {
    int i,j;
    for(i=0; i<3; ++i)
    for(j=0; j<2; ++j)
    {
        int p,q;
        for(p=sz(words[i][j])-1, q=sz(vec[k])-1; 
            p>=0 && q>=0 && words[i][j][p]==vec[k][q]; --p,--q);
        if (p<0) { good=true; goto done; } // found match words[][]
    }
    done:
    if (!good) break;
    types.push_back(i); genders.push_back(j);
    }
    if (!good) { cout << "NO" << endl; return 0; }
    if (sz(vec)==1) { cout << "YES" << endl; return 0; }
    
    //for(int i=0; i<int(types.size()); ++i)
    //    cout << types[i] << ',' << genders[i] << "     ";
    //cout << endl;

    int cnt[3]={0};
    int gender[2]={0};
    for(int t=0,k=0; t<3; ++t)
    {
        for(; k<int(types.size()); ++k)
        { 
            gender[genders[k]]++;
            if (types[k]==t) cnt[t]++; else break; 
        }
    }
    good = true;
    if (cnt[0]+cnt[1]+cnt[2] < int(vec.size())) good=false;
    if (cnt[1]!=1) good=false;
    if (gender[0]>=1 && gender[1]>=1) good=false;

    if (good) cout << "YES" << endl;
    else cout << "NO" << endl;

}

// 683034   Sep 8, 2011 11:27:25 PM     lantimilan  A - Grammar Lessons     GNU
// C++  Accepted    30 ms   1600 KB 
// 682598   Sep 8, 2011 11:02:09 PM     lantimilan  A - Grammar Lessons     GNU
// C++  Accepted    50 ms   1600 KB
// 682540   Sep 8, 2011 11:00:20 PM     lantimilan  A - Grammar Lessons     GNU
// C++  Wrong answer on test 15     30 ms   1400 KB
// 682380   Sep 8, 2011 10:55:10 PM     lantimilan  A - Grammar Lessons     GNU
// C++  Wrong answer on test 3  30 ms   1400 KB
// 682254   Sep 8, 2011 10:50:36 PM     lantimilan  A - Grammar Lessons     GNU
// C++  Wrong answer on test 2  10 ms   1400 KB 
