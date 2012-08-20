// =========================================================
// 
//       Filename:  D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/02/2012 11:22:28 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/02/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
using namespace std;

typedef pair<int,int> pii;
vector<pii> vec;
map<string,int> mpphone, mpemail;
int N; 
int P, E;
bool seen[20005];

void dfs(int s)
{
    seen[s]=true;
    for(int i=0; i<N; ++i) if (!seen[i]) {
        if (vec[s].first == vec[i].first || vec[s].second == vec[i].second)
            dfs(i);
    }
}

int main()
{
    cin >> N; cin.ignore(1024,'\n');
    for(int i=0; i<N; ++i) {
        string line; getline(cin, line);
        //cout << line << endl;
        // skip 4 commas
        int pos, cnt;
        for(pos=0, cnt=0; cnt<4; pos++) {
            if (line[pos]==',') cnt++;
        }
        assert(line[pos-1]==',');
        // get phone
        for(; !isdigit(line[pos]); pos++); // skip nondigit
        int start=pos;
        for(; isdigit(line[pos]); pos++);
        string phone = line.substr(start, pos-start);
        // get email
        for(; !('a'<=line[pos] && line[pos]<='z'); pos++);
        string email = line.substr(pos); //cout << email << endl;
        if (!mpphone.count(phone)) mpphone[phone]=P++;
        if (!mpemail.count(email)) mpemail[email]=E++;
        vec.push_back(pii(mpphone[phone], mpemail[email]));
    }
    int ans=0;
    for(int i=0; i<N; ++i) if (!seen[i]) {
        ans++; dfs(i);
    }
    cout << ans << endl;
}
