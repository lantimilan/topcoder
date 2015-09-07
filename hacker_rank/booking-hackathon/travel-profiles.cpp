// travel-profiles.cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

set<string> facs[105];
int prices[105];
int ids[105];

bool is_subset(const set<string> &s1, const set<string> &s2) {
    for (auto &elt : s1) {
        if (!s2.count(elt)) return false;
    }
    return true;
}

void solve(int N) {
    string line; getline(cin, line);
    istringstream iss(line);
    int budget; iss >> budget;
    set<string> fac;
    string token;
    while (iss >> token) {
        fac.insert(token);
    }
    vector<pair<pair<int, int>, int>> ans;
    for (int i = 0; i < N; ++i) {
        if (budget >= prices[i] && is_subset(fac, facs[i])) {
            int num = facs[i].size();
            ans.push_back(make_pair(
                make_pair(-num, prices[i]),
                ids[i]));
        }
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i].second;
    }
    cout << endl;
}

int main() {
    int N; cin >> N; cin.ignore();
    for (int i = 0; i < N; ++i) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        iss >> ids[i] >> prices[i];
        string token;
        while (iss >> token) {
            facs[i].insert(token);
        }
    }
    int M; cin >> M; cin.ignore();
    while (M--) {
        solve(N);
    }
}
