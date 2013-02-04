// bipartite matching
// but how to get lexico minimum matching

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int V[300];
int adj[300][300];
int mate[300];
int vis[300];

bool augment(int n, int s)
{
    vis[s] = 1;
    bool ans = false;
    int j;
    for (j=n; j<2*n; ++j) if (adj[s][j] && !vis[j]) {
        vis[j] = 1;
        if (mate[j] < 0) { ans = true; break; }
        else {
            int next = mate[j];
            if (augment(n, next)) { ans = true; break; }
        }
    }
    if (ans) { mate[s] = j; mate[j] = s; }
    return ans;
}

int bipartite(int n)
{
    int ans = 0;
    while (true) {
        bool update = false;
        for (int s=0; s<n; ++s) if (mate[s] < 0) {
            memset(vis, 0, sizeof vis);
            if (augment(n, s)) { ans++; update = true; break; }
        }
        if (!update) break;
    }
    return ans;
}

bool match(const string &s1, const string &s2)
{
    for (int i=0; i<s1.length(); ++i)
        if (s1[i]=='?' || s2[i]=='?') continue;
        else if (s1[i] != s2[i]) return false;
    return true;
}

void solve(int tcase)
{
    memset(adj, 0, sizeof adj);
    memset(mate, -1, sizeof mate);
    int m; cin >> m;
    string s1, s2; cin >> s1 >> s2;
    string left[105], right[105];
    int l = s1.length();
    int sub = l/m;
    for (int i=0, j=0; i<l; i+=sub, j++) {
        left[j] = s1.substr(i, sub);
        right[j] = s2.substr(i, sub);
    }
    for (int i=0; i<m; ++i) {
        for (int j=m; j<2*m; ++j) {
            if (match(left[i], right[j-m])) {
                adj[i][j] = adj[j][i] = 1;
                //cout << "edge " << i << " " << j-m << endl;
            }
        }
    }
    int size = bipartite(m);
    cout << "Case #" << tcase << ": ";
    if (size < m) { cout << "IMPOSSIBLE" << endl; return; }
    // look for lexico smallest match
    cout << "perfect match" << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
