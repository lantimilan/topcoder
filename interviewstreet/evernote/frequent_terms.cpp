// =========================================================
// 
//       Filename:  frequent_terms.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/11/2012 10:22:02 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/11/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

map<string,int> term_map;
vector<pair<int,string> > vec;

int main()
{
    int n; cin >> n; cin.ignore(1024, '\n');
    for(int i=0; i<n; ++i) {
        string line;
        getline(cin, line);
        term_map[line]++;
    }
    for(map<string,int>::iterator it=term_map.begin();
        it != term_map.end(); ++it) {
        vec.push_back(make_pair(-it->second, it->first));
        }
    sort(vec.begin(), vec.end());
    int k; cin >> k;
    for(int i=0; i<k; ++i) {
        cout << vec[i].second << endl;
    }
}
