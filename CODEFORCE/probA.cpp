// =========================================================
// 
//       Filename:  probA.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/23/2011 08:10:04 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/23/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
typedef vector<vector<pii> > vvi; // dest,cap

const int MAX = 1000000+5;
int main()
{
    int n,p; cin >> n >> p;
    int indeg[1005]={0}, outdeg[1005]={0};
    vvi adj(n,vector<pii>());

    for(int i=0; i<p; ++i)
    {
        int a,b,d; cin >> a >> b >> d; --a; --b;
        adj[a].push_back(pii(b,d));
        outdeg[a]=1; indeg[b]=1;
    }

    vector<pair<pii,int> > ans;
    for(int i=0; i<n; ++i) if (outdeg[i] && indeg[i]==0)
    {
        int water=MAX, curr=i, next=i;
        while(outdeg[curr]) {
            next = adj[curr][0].first;
            water=min(water, adj[curr][0].second);
            curr = next;
        }
        ans.push_back(make_pair(pii(i,curr),water));
    }
    cout << ans.size() << endl;
    for(size_t i=0; i<ans.size(); ++i)
        cout << ans[i].first.first+1 << ' ' 
            << ans[i].first.second+1 << ' ' << ans[i].second << endl;
}
