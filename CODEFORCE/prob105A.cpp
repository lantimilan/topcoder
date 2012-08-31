////////////////////////////////////////////////////////
// http://codeforces.com/contest/105/problem/A
//
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

void solve()
{
    int n,m; double k; cin >> n >> m >> k;
    map<string, int> skills;
    for(int i=0; i<n; ++i)
    { 
        string sk; int level; cin >> sk >> level;
        skills[sk]=level;
    }
    map<string,int> ans;
    for(map<string,int>::iterator it=skills.begin(); it!=skills.end(); ++it)
    {
        it->second = int(it->second*k+1.0e-6); // got hacked, need to add 1.0e-6 here
        if (it->second>=100) ans[it->first]=it->second;
    }
    for(int i=0; i<m; ++i)
    {
        string sk; cin >> sk;
        if (skills.count(sk)) {
            if (skills[sk]<100) ans[sk]=0;
        }
        else ans[sk]=0;
    }
    cout << ans.size() << endl;
    for(map<string,int>::iterator it=ans.begin(); it!=ans.end(); ++it)
        cout << it->first << ' ' << it->second << endl;
}
int main()
{
    solve();
}
