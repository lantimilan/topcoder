// pairing.cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef pair<string, pair<string, int>> triple;
map<triple, pair<int,int>> lookup;

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        string company;
        int size;
        string color;
        string type;
        cin >> company >> size >> color >> type;
        triple t = make_pair(company, make_pair(color, size));
        if (type == "L") {
            lookup[t].first++;
        } else {
            lookup[t].second++;
        }
    }
    int ans = 0;
    for (auto &entry : lookup) {
        ans += min(entry.second.first, entry.second.second);
    }
    cout << ans << endl;
}
