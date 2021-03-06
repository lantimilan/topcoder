// lcs3.cpp
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef pair<pair<int,int>,int> triple;
const int M = 3000;
// because the array is generated by a[i] = i with pr = 1/N
// then for each triple (i1,i2,i3) the prob that they are equal is 1/N^2
// E[triples that match] = N^3 * 1/N^2 = N
// so we can work on the triples
int N;
map<triple,int> lcs;
vector<int> s1[M+5];
vector<int> s2[M+5];
vector<int> s3[M+5];

void chmax(int &x, int y) {
    if (x < y) x = y;
}

void solve() {
    cin >> N;
    for (int i = 0; i <= N; ++i) {
        s1[i].clear();
        s2[i].clear();
        s3[i].clear();
    }
    lcs.clear();

    for (int i = 0; i < N; ++i) {
        int v; cin >> v;
        s1[v].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        int v; cin >> v;
        s2[v].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
        int v; cin >> v;
        s3[v].push_back(i);
    }

    for (int v = 1; v <= M; ++v) {
        for (int k1 : s1[v])
        for (int k2 : s2[v])
        for (int k3 : s3[v]) {
            lcs[make_pair(make_pair(k1,k2), k3)] = 1;
        }
    }

    map<triple,int>::iterator it, it2;
    for (it = lcs.begin(); it != lcs.end(); ++it) {
        for (it2 = lcs.begin(); it2 != it; ++it2) {
            triple t = it->first;
            triple t2 = it2->first;
            if (t.first.first > t2.first.first &&
                t.first.second > t2.first.second &&
                t.second > t2.second) {
                    chmax(lcs[t], lcs[t2]+1);
                }
        }
    }

    int ans = 0;
    for (auto p : lcs) {
        chmax(ans, p.second);
    }
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}

// AC
