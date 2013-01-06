// separate color=0 and 1 into two parts
// edge can go only from one part to the other
// find min s[v] and connect to the max s[w] on the other part
//
// Use heap or BST (stl set) to get min and max and update in O(log n) time
//
// Correctness from induction

#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int pa[100000+5];
int rank[100000+5];
int color[100000+5];
set<pii> bipart[2]; // 0 white, 1 black, (s[v], id)
vector<pair<int, pii> > edges;  // weight, (u, v)
vector<int> leaders;

int myfind(int u)
{
    while (pa[u] != u) u = pa[u];
    return u;
}

void myunion(int p1, int p2)
{
    if (rank[p1] < rank[p2]) { pa[p1] = p2; }
    else if (rank[p1] > rank[p2]) { pa[p2] = p1; }
    else { pa[p1] = p2; rank[p2]++; }
}

int main()
{
    int n; cin >> n;
    // init
    for (int c=0; c<2; ++c)
        bipart[c].clear();
    edges.clear();
    leaders.clear();
    for (int i=0; i<n; ++i) {
        int c, s; cin >> c >> s;
        color[i] = c;
        if (s > 0)
            bipart[c].insert(pii(s, i));
    }

    while (!bipart[0].empty()) {
        pii p[2];
        int cmin, s[2];
        for (int c=0; c<2; ++c)
            p[c] = *(bipart[c].begin());
        for (int c=0; c<2; ++c)
            s[c] = p[c].first;
        cmin = s[0] < s[1] ? 0 : 1;

        int cc, ss, id;
        ss = s[cmin];
        id = p[cmin].second;
        cc = cmin;
        bipart[cc].erase(bipart[cc].begin());
        set<pii>::iterator it = bipart[1-cc].end(); --it;
        pii mate = *it; bipart[1-cc].erase(it);
        edges.push_back(make_pair(ss, pii(id, mate.second)));
        mate.first -= ss;
        assert(mate.first >= 0);
        if (mate.first > 0) bipart[1-cc].insert(mate);
    }
    //cout << "edges " << edges.size() << endl;
    // now all s[v] is zero
    // connect the components using w(e)=0 edges
    // can only connect different color vertex
    for (int i=0; i<n; ++i) { pa[i] = i; rank[i] = 0; }
    for (int i=0; i<int(edges.size()); ++i) {
        int u, v, p1, p2;
        u = edges[i].second.first;
        v = edges[i].second.second;
        p1 = myfind(u);
        p2 = myfind(v);
        if (p1 != p2) { myunion(p1, p2); }
    }
    // connect everyone to center[0] and center[1]
    int center[2];
    for (int c=0; c<2; ++c) {
        for (int i=0; i<n; ++i) if (color[i] == c) { center[c] = i; break; }
    }

    for (int i=0; i<n; ++i) {
        int p = myfind(i);
        for (int c=0; c<2; ++c) {
            int p2 = myfind(center[c]);
            if (color[p] != c && p != p2) {
                myunion(p, p2);
                edges.push_back(make_pair(0, pii(p, center[c])));
            }
        }
    }

    if (myfind(center[0]) != myfind(center[1])) {
        myunion(center[0], center[1]);
        edges.push_back(make_pair(0, pii(center[0], center[1])));
    }

    assert(edges.size() == n-1);
    for (int i=0; i<int(edges.size()); ++i) {
        cout << 1+edges[i].second.first << ' '
            << 1+edges[i].second.second << ' '
            << edges[i].first << '\n';
    }
}

// Accepted, finally
// use assertion
// when all s[v] is zero, use union-find
