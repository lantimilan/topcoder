// =========================================================
// 
//       Filename:  prob67B.cpp
// 
//    Description:  B. Facetook Priority Wall
// 
//        Version:  1.0
//        Created:  04/13/2011 08:14:57 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/13/2011, LI YAN
// 
// =========================================================
//
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void solve()
{
    string me; cin >> me;
    int n; cin >> n; cin.ignore(1024,'\n');
    map<string,int> priomap;

    for(int x=0; x<n; ++x) {
    string line, word;
    getline(cin, line);
    vector<string> vs;
    istringstream iss(line);
    while(iss>>word) vs.push_back(word);
    if (vs[1] == "posted") {
        string a = vs[0]; string b = vs[3]; int len = b.length();
        b = b.substr(0,len-2);
        if (a!=me) { if (b==me) priomap[a] += 15; else priomap[a]+=0; }
        if (b!=me) { if (a==me) priomap[b] += 15; else priomap[b]+=0; }
    }
    else if (vs[1] == "commented") {
        string a = vs[0]; string b = vs[3]; int len = b.length();
        b = b.substr(0,len-2);
        if (a!=me) { if (b==me) priomap[a] += 10; else priomap[a]+=0; }
        if (b!=me) { if (a==me) priomap[b] += 10; else priomap[b]+=0; }
    }
    else { // vs[1] is likes
        string a = vs[0]; string b = vs[2]; int len = b.length();
        b = b.substr(0,len-2);
        if (a!=me) { if (b==me) priomap[a] += 5; else priomap[a]+=0; }
        if (b!=me) { if (a==me) priomap[b] += 5; else priomap[b]+=0; }
    }
    }
    typedef pair<int,string> PIS;
    vector<PIS> vp;
    map<string,int>::const_iterator cit;
    for(cit=priomap.begin(); cit!=priomap.end(); ++cit)
        vp.push_back(make_pair(-cit->second, cit->first)); // value_type
    sort(vp.begin(), vp.end());
    for(int i=0; i<int(vp.size()); ++i)
        cout << vp[i].second << endl;
}
int main()
{
    solve();
}

