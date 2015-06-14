#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

void solve(int tcase) {
    int N, R; cin >> N >> R;
    vector<set<int> > graph(N);
    vector<int> indeg(N);
    for (int i = 0; i < R; ++i) {
        int u, v; cin >> u >> v;
        bool inserted = graph[v].insert(u).second;
        if (inserted) indeg[u]++;
    }

    vector<int> mark(N);
    int zerocnt = 0;
    int semester;
    for (int l = 0; l < N; ++l) {
        vector<int> vec;
        for (int i = 0; i < N; ++i) if (!mark[i] && indeg[i] == 0) {
            mark[i] = 1; zerocnt++;
            vec.push_back(i);
        }
        if (zerocnt >= N) { semester = l+1; break; }
        vector<int>::iterator vit;
        for (vit = vec.begin(); vit != vec.end(); ++vit) {
            set<int>::iterator sit;
            for (sit = graph[*vit].begin(); sit != graph[*vit].end(); ++sit) {
                indeg[*sit]--;
            }
        }
    }

    if (zerocnt < N) {
        printf("Case %d: Never Ends\n", tcase);
    } else {
        printf("Case %d: %d semester(s)\n", tcase, semester);
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
    return 0;
}
