// prob574B.cpp
#include <iostream>
#include <set>
using namespace std;

set<int> warriors[4005];

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        warriors[a].insert(b);
        warriors[b].insert(a);
    }

    int recognition = -1;
    for (int first = 0; first < n; ++first) {
        for (int second : warriors[first]) {
            for (int third : warriors[second]) if (warriors[first].count(third)) {
                int curr = warriors[first].size() + warriors[second].size() + warriors[third].size();
                curr -= 2 * 3;
                if (recognition < 0 || recognition > curr) {
                    recognition = curr;
                }
            }
        }
    }
    cout << recognition << endl;
}
