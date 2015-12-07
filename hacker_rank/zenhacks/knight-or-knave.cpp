// knight-or-knave.cpp
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;

// a collection of disjoint cycles, only two assignments are possible

int N;
int X[100000+5];
int vis[100000+5];
int indeg[100000+5];
string ans;
vector<int> cycle;

void dfs(int s) {
    vis[s] = 1;
    cycle.push_back(s);
    int next = X[s];
    if (next < 0) next = -next;
    if (!vis[next]) dfs(next);
}

char getcharbool(bool b) {
    return b ? 'A' : 'B';
}

bool consistent(const vector<pair<int,char>> &assign) {
    map<int,char> mp;
    for (auto &p : assign) {
        int k = p.first;
        int v = p.second;
        if (mp.count(k) && mp[k] != v) return false;
        mp[k] = v;
    }
    return true;
}

void print_assign(const vector<pair<int,char>> &assign) {
    cout << "assign: ";
    for (auto &p : assign) { cout << "(" << p.first << "," << p.second << ")" << " "; }
    cout << endl;
}

vector<pair<int,char>> set_truth(bool start) {
    int l = cycle.size(); //cout << l << endl;
    vector<pair<int,char>> assign(l+1);
    bool curr = start;
    assign[0] = make_pair(cycle[0], getcharbool(start));
    for (int i = 0; i < l; ++i) {
        int pos = cycle[i];
        int predict = X[pos];
        int next;
        if (curr) {
            next = (predict > 0);
        } else {
            next = !(predict > 0);
        }
        int i2 = i+1;
        assign[i2].first = abs(predict);
        assign[i2].second = getcharbool(next);
        //cout << "set_truth "  << assign[i2].first << ' ' << assign[i2].second << endl;
        curr = next;
    }
    //cout << "set_truth: "; print_assign(assign);
    return assign;
}

bool is_better(const vector<pair<int,char>> &s1,
    const vector<pair<int,char>> &s2) {
    bool b1 = consistent(s1);
    bool b2 = consistent(s2);
    assert(b1 || b2);
    if (!b1) return false;
    if (!b2) return true;

    map<int,char> mp1, mp2;
    for (int i = 0; i < s1.size(); ++i) mp1[s1[i].first] = s1[i].second;
    for (int i = 0; i < s2.size(); ++i) mp2[s2[i].first] = s2[i].second;

    int c1 = 0, c2 = 0;
    for (auto &p : mp1) c1 += (p.second == 'A');
    for (auto &p : mp2) c2 += (p.second == 'A');
    if (c1 != c2) return c1 > c2;

    for (auto &p : mp1) {
        int k = p.first;
        char v = p.second;
        assert(mp2.count(k));
        if (v != mp2[k]) return v == 'A';
    }
    return true;
}

vector<pair<int,char>> process() {
    vector<pair<int,char>> assign1, assign2;
    assign1 = set_truth(true);
    assign2 = set_truth(false);
    if (is_better(assign1, assign2)) return assign1;
    else return assign2;
}

void solve() {
    memset(indeg, 0, sizeof indeg);
    memset(vis, 0, sizeof vis);
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> X[i];
        int p = abs(X[i]);
        indeg[p]++;
    }

    ans = string(N, ' ');
    for (int i = 1; i <= N; ++i) if (indeg[i] == 0) {
        assert(!vis[i]);
        cycle.clear();
        dfs(i);
        //cout << "first\n"; for (int v : cycle) cout << v << ' '; cout << endl;
        vector<pair<int,char>> assign = process();
        assert(!assign.empty());
        assign.pop_back();
        for (auto &p : assign) {
            int pos = p.first;
            char ch = p.second;
            assert(ans[pos-1] == ' ');
            ans[pos-1] = ch;
        }
    }
    for (int i = 1; i <= N; ++i) if (!vis[i]) {
        assert(!vis[i]);
        cycle.clear();
        dfs(i);
        //cout << "second\n"; for (int v : cycle) cout << v << ' '; cout << endl;
        vector<pair<int,char>> assign = process();
        assert(!assign.empty());
        assign.pop_back();
        //cout << "assign: "; for (auto &p : assign) { cout << "(" << p.first << "," << p.second << ")" << " "; } cout << endl;
        for (auto &p : assign) {
            int pos = p.first;
            char ch = p.second;
            //cout << pos << ' ' << ch << endl;
            assert(ans[pos-1] == ' ');
            ans[pos-1] = ch;
        }
    }
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
