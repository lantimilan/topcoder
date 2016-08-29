// good-memories.cc
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string &line) {
    vector<string> vec;
    int n = line.length();
    int i, j;
    for (i = 0; i < n; i = j+1) {
        for (j = i+1; j < n && line[j] != ','; ++j)
            ;
        string s = line.substr(i, j-i);
        vec.push_back(s);
    }
    return vec;
}

int D;
map<string, int> nodes;
set<int> graph[4005];
int indeg[4005];

void solve() {
    D = 0; nodes.clear();
    for (int i = 0; i < 4005; ++i) graph[i].clear();
    memset(indeg, 0, sizeof indeg);

    int n; cin >> n; cin.ignore(1024, '\n');
    for (int i = 0; i < n; ++i) {
        string line; getline(cin, line);
        vector<string> places = split(line);
        int n = places.size();
        for (int i = 0; i < n; ++i) {
            if (!nodes.count(places[i])) {
                nodes[places[i]] = D++;
            }
        }
        for (int i = 0; i+1 < n; ++i) {
            string s1 = places[i];
            string s2 = places[i+1];
            int x1 = nodes[s1];
            int x2 = nodes[s2];
            graph[x1].insert(x2);
        }
    }
    for (int i = 0; i < D; ++i) {
        for (int next : graph[i]) {
            indeg[next]++;
        }
    }

/////////////////////////////////////////////
//    for (auto p : nodes) {
//        cout << p.first << " => " << p.second << endl;
//    }
//    for (int i = 0; i < D; ++i) {
//        cout << i << ": ";
//        for (int next : graph[i]) {
//            cout << next << " ";
//        }
//        cout << endl;
//    }
/////////////////////////////////////////////

    queue<int> que;
    for (int i = 0; i < D; ++i) if (indeg[i] == 0) {
        que.push(i);
    }
    int cnt = 0;
    while (!que.empty()) {
        int s = que.front(); que.pop(); cnt++;
        for (int next : graph[s]) {
            indeg[next]--;
            if (indeg[next] == 0) {
                que.push(next);
            }
        }
    }
    string good = "ORDER EXISTS";
    string bad = "ORDER VIOLATION";
    cout << (cnt >= D ? good : bad) << endl;
}

int main() {
    int cases = 0;
    cin >> cases;
    while (cases--) {
        solve();
    }
}
