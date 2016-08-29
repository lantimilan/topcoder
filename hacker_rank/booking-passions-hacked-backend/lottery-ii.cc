// lottery-ii.cc
// bipartite matching, assign person to event
// person p has an edge to event e iff
// person p interest list intersects event e passion
// list
//
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;


set<string> people[105];
set<string> events[105];

vector<int> graph[205];
int mate[205];
int vis[205];
int N;

bool augment(int s) {
    // cout << "augment " << s << endl;
    vis[s] = 1;
    for (int next : graph[s]) {
        if (mate[next] < 0) { mate[s] = next; mate[next] = s; return true; }
        int snew = mate[next];
        if (!vis[snew] && augment(snew)) {
            mate[s] = next; mate[next] = s; return true;
        }
    }
    return false;
}

int bipartite() {
    int ans = 0;
    for (int i = 0; i < N; ++i) if (mate[i] < 0) {
        memset(vis, 0, sizeof vis);
        if (augment(i)) ans++;
    }
    return ans;
}

bool overlap(const set<string> &s1, const set<string> &s2) {
    for (const string &s : s1) {
        if (s2.count(s)) return true;
    }
    return false;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int t; cin >> t;  // ticket, ignored
        int c; cin >> c;
        for (int j = 0; j < c; ++j) {
            string s; cin >> s;
            people[i].insert(s);
        }
    }
    for (int i = 0; i < N; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            string s; cin >> s;
            events[i].insert(s);
        }
    }
    for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) {
        if (overlap(people[i], events[j])) {
            graph[i].push_back(j+N);
            graph[j+N].push_back(i);
        }
    }

//    for (int i = 0; i < 2*N; ++i) {
//        cout << i << ": ";
//        for (int j : graph[i]) cout << j << " ";
//        cout << endl;
//    }

    memset(mate, -1, sizeof mate);
    int ans = bipartite();
    cout << ans << endl;
}
