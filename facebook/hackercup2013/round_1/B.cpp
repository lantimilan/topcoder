// bipartite matching
// but how to get lexico minimum matching
//
// previous solution sorts edge by matched string (breaks when ties)
// the correct idea is to try every a-f for ?

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<string, int> psi;

vector<psi> adj[300];

int V[300];
int mate[300];
int vis[300];

bool augment(int n, int s)
{
    vis[s] = 1;
    bool ans = false;
    int i, j;
    for (i=0; i<adj[s].size(); ++i) {
        j = adj[s][i].second;
        if (vis[j]) continue;
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

string get_str(const string &s1, const string &s2)
{
    string ans = s1;
    for (int i=0; i<s1.length(); ++i) {
        if (s1[i] != '?') ans[i] = s1[i];
        else if (s2[i] != '?') ans[i] = s2[i];
        else ans[i] = 'a';
    }
    return ans;
}

bool check(int m, const string &s1, const string &s2)
{
    memset(mate, -1, sizeof mate);
    for (int i=0; i<300; ++i) adj[i].clear();

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
                string s = get_str(left[i], right[j-m]);
                adj[i].push_back(psi(s,j));
            }
        }
    }
    for (int i=0; i<m; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }
    int size = bipartite(m);
    return size == m;
}

void solve(int tcase)
{
    int m; cin >> m;
    string s1, s2; cin >> s1 >> s2;
    if (!check(m, s1, s2)) {
        cout << "Case #" << tcase << ": ";
        cout << "IMPOSSIBLE" << endl; return;
    }
    for (int i=0; i<s1.length(); ++i) if (s1[i] == '?')
    {
    for (s1[i] = 'a'; s1[i] <= 'f'; ++s1[i])
    {

    memset(mate, -1, sizeof mate);
    for (int i=0; i<300; ++i) adj[i].clear();

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
                string s = get_str(left[i], right[j-m]);
                adj[i].push_back(psi(s,j));
                //adj[j].push_back(psi(s,i));
                //cout << "edge " << i << " " << j-m << endl;
            }
        }
    }
    for (int i=0; i<m; ++i) {
        sort(adj[i].begin(), adj[i].end());
    }
    int size = bipartite(m);
    if (size == m) break;
    }
    assert(s1[i] <= 'f');
    }
    cout << "Case #" << tcase << ": " << s1 << endl;;
    // look for lexico smallest match
    //cout << "perfect match" << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
