// template.cpp
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

bool check(const vector<int> &vec) {
    int maxpos = 0;
    int n = vec.size();
    for (int i = 1; i < n; ++i) if (vec[i] > vec[maxpos]) maxpos = i;
    for (int i = 0; i < maxpos; ++i) if (vec[i] > vec[i+1]) return false;
    for (int i = maxpos + 1; i < n; ++i) if (vec[i-1] < vec[i]) return false;
    return true;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N; cin >> N;
    vector<int> A(N); for (int i = 0; i < N; ++i) cin >> A[i];

    for (int i = 0; i < N; ++i) cout << A[i] << ' '; cout << endl;

    int best = N*N + 10;
    queue<vector<int> > que; que.push(A);
    map<vector<int>, int> dist; dist[A] = 0;
    while (!que.empty()) {
        vector<int> cur = que.front(); que.pop();
        int d = dist[cur];
        if (check(cur)) { best = d; break; }

        cout << "best " << d << " : ";
        for (int i = 0; i < cur.size(); ++i) cout << cur[i] << ' ';
        cout << endl;

        for (int i = 0; i < cur.size(); ++i)
        for (int j = 0; j < cur.size(); ++j) {
            vector<int> next = cur;
            int val = next[i];
            if (i > j) {
                for (int k = i-1; k >= j; --k) next[k+1] = next[k];
            } else {
                for (int k = i+1; k <=j; ++k) next[k] = next[k+1];
            }
            next[j] = val;
            if (!dist.count(next)) {
                dist[next] = d + abs(j-i); que.push(next);
            }
        }
    }
    cout << best << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
