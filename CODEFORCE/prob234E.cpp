// =========================================================
// 
//       Filename:  prob234E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 01:24:30 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, string> pis;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n; fin >> n;
    int x, a, b, c; fin >> x >> a >> b >> c;

    int m = n/4;
    vector<pis> teams(n);
    vector<pis> baskets[4];
    for(int i=0; i<n; ++i) {
        string name; fin >> name;
        int rate; fin >> rate;
        teams[i] = pis(rate, name);
    }
    sort(teams.begin(), teams.end());
    reverse(teams.begin(), teams.end());
    for(int i=0; i<4; ++i) {
        for(int j=0; j<m; ++j) {
            baskets[i].push_back(teams[i*m+j]);
        }
    }

    for(int i=0; i<m-1; ++i) {
        fout << "Group " << char(i+'A') << ":\n";
        for(int j=0; j<4; ++j) {
            int y = (x*a + b) % c;
            int s = baskets[j].size();
            x = y;
            y %= s;
            fout << baskets[j][y].second << "\n";
            baskets[j].erase(baskets[j].begin() + y);
        }
    }
    fout << "Group " << char(m-1+'A') << ":\n";
    for(int i=0; i<4; ++i) {
        fout << baskets[i][0].second << "\n";
    }
}
