// catvsdog.cpp
//
// T is 100
// c, d is 100
// v is 500
//
// must be bipartite matching with O(nm) = 100 * 500
// and for 100 testcases, total is 10^6
//
// finally got the puzzle, after 12 hours of thinking
// it is bipartite independent set indeed
//
// each vote (c1, d1) or (d2, c2) is a node in the graph
// two nodes are connected by an edge if they conflict
// that is, either d1 = d2 or c1 = c2.
// note that votes of type (c1, d1) and (c2, d2) can never conflict
//
// Now the difficult part: why each vote must be one C and one D?
// What if some vote can be (c1, c2) or (d1, d2)?
//
// We know independent set in general is a difficult problem, not
// so if the graph is bipartite, so the graph better be bipartite
// and it indeed is!
//
// For a graph to be bipartite, a sufficient and necessary condition
// is no odd length cycle, and let us consider any cycle
// (c1, d1) - (d1, c2) - (c2, d2) - ... - (d_k, c_k+1)
// to complete a cycle that second component of the last vote must be C
// and we have c1 = c_k+1
// however we can only end at C if we have even number of nodes in this cycle
// and cycle with even number of nodes have even number of edges
// for otherwise we must end at some D in this path and thus cannot complete
// a cycle
//
// The rest is now easy
// We have 500 nodes, each node can conflict with at most two other nodes, so
// the number of edges is at most 500 * 2 = 1000
// To solve independent set problem for a bipartite graph amounts to solve a
// matching problem which can be done in O(nm) time, 500 * 1000 = 5 * 10^5
// For 100 testcases we need 100 * 5 * 10^5 = 5 * 10^7 time
//
// this concludes the algorithm analysis of this problem
//
// Actually NO, each vote can conflict with every other vote so edge could be
// as many as 500^2, then it is too slow for 100 testcases
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

pair<string, string> votes[505];
vector<int> adj[505];
int parity[505];
int mate[505];
int vis[505];
int C, D, V;

bool dfs(int s, int p)
{
    parity[s] = p;
    for (int x = 0; x < adj[s].size(); ++x) {
        int b = adj[s][x];
        if (parity[b] < 0) {
            bool next = dfs(b, 1-p);
            if (!next) return false;
        } else {
            if (parity[b] == parity[s]) {
                return false;
            }
        }
    }
    return true;
}

bool is_bipartite()
{
    memset(parity, -1, sizeof parity);
    for (int i = 0; i < V; ++i) if (parity[i] < 0)
        if (!dfs(i, 0)) return false;
    return true;
}

bool augment(int s)
{
    vis[s] = 1;
    for (int x = 0; x < adj[s].size(); ++x) {
        int b = adj[s][x];
        if (mate[b] < 0) {
            mate[s] = b; mate[b] = s; return true;
        } else {
            int d = mate[b];
            if (!vis[d] && augment(d)) {
                mate[s] = b; mate[b] = s; return true;
            }
        }
    }
    return false;
}

int matching()
{
    memset(mate, -1, sizeof mate);
    int ans = 0;
    bool update = true;
    while (update) {
        update = false;
        memset(vis, 0, sizeof vis);
        for (int s = 0; s < V; ++s) if (mate[s] < 0) {
            if (augment(s)) { update = true; ans++; break; }
        }
    }
    return ans;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        cin >> C >> D >> V;
        //cout << C << ' ' << D << ' ' << V << endl;
        for (int i = 0; i < V; ++i) {
            string keep, away;
            cin >> keep >> away;
            votes[i] = make_pair(keep, away);
        }
        for (int i = 0; i < V; ++i) adj[i].clear();
        for (int i = 0; i < V; ++i)
        for (int j = i+1; j < V; ++j)
        if (votes[i].first == votes[j].second || votes[i].second == votes[i].first)
        {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
        assert(is_bipartite());
        int m = matching();
        cout << V - m << endl;
    }
}

// got WA
