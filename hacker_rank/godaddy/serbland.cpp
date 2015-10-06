// serbland.cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
using namespace std;

set<pair<int,long long>> ys; // yi, diamond

const int M = 100000;

pair<pair<int,int>,int> diamonds[M+5];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        diamonds[i] = make_pair(make_pair(x,y), w);
    }
    sort(diamonds, diamonds + n);

    for (int i = n-1; i >= 0; --i) {
        int x = diamonds[i].first.first;
        int y = diamonds[i].first.second;
        int w = diamonds[i].second;

        set<pair<int,long long>>::iterator it;
        it = ys.lower_bound(make_pair(y,0LL));
        set<pair<int,long long>>::iterator start, end;
        long long curr;
        if (it == ys.end()) {
            curr = w;
            start = end = it;
        } else {
            curr = w + it->second;
            start = end = it;
            if (end->first == y) ++end;
        }
        if (start != ys.begin()) {
        for (--start; start != ys.begin(); --start) {
            if (start->second > curr) break;
        }
        }
        if (start != ys.begin()) {
            ++start;
        } else {
            if (start->second > curr) ++start;
        }
        ys.erase(start, it);
        ys.insert(make_pair(y, curr));
    }

    cout << ys.begin()->second << endl;
}
