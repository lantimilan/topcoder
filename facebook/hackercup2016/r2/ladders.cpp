// ladders.cpp
#include <iostream>
#include <map>
#include <set>
using namespace std;

map<int, set<int>> ladders;

void solve(int tcase) {
    ladders.clear();

    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int x, h; cin >> x >> h;
        ladders[h].insert(x);
    }


    // output
    cout << "Case #" << tcase << ": ";
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
