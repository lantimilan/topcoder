// http://codeforces.ru/contest/8/problem/B
// 512MB memory dp[1<<24] is fine, dp[1<<26][26] is too much
//
// most people solve with DP
// can also use min weight matching to solve
//
#include <map>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

#define sz(a) int(a.size())

typedef pair<int,int> pii;

const char ops[]="URDL";
const int dir[][2]={{-1,0},{0,+1},{+1,0},{0,-1}};

int main()
{
    map<pii,int> dist;
    string s; cin >> s;
    pii pos(0,0);
    dist[pos]=0;
    bool good=true;
    for(int i=0; i<sz(s); ++i)
    {
        int x;
        for(x=0; x<4; ++x)       
        { if (ops[x]==s[i]) break; }
        pos.first += dir[x][0];
        pos.second += dir[x][1];
        if (dist.count(pos)) { good=false; break; }
        else dist[pos]=i+1;
    }
    if (good) {
        // bfs
        queue<pii> que; que.push(pii(0,0));
        while(!que.empty()) {
            pii node = que.front(); que.pop();
            for(int x=0; x<4; ++x)
            {
                pii next; next.first=node.first+dir[x][0];
                next.second=node.second+dir[x][1];
                if (dist.count(next)) {
                    if (dist[next]>dist[node]+1) { good=false; goto done;}
                    else if (dist[next]==dist[node]+1) que.push(next);
                    else {} // backward edge ignored
                }
            }
        }
        done:
        if (good) cout << "OK" << endl;
        else cout << "BUG" << endl;
    }
    else cout << "BUG" << endl;
}
