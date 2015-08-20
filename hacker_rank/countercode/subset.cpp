// subset.cpp
#include <cassert>
#include <iostream>
#include <map>
using namespace std;

int cnt[1<<17];

void update(int pos, int d) {
    while (true) {
        cnt[pos] += d;
        if (pos == 0) break;
        else pos = (pos-1) / 2;
    }
}

int main() {
    int Q; cin >> Q;
    while (Q--) {
        string op; int val; cin >> op >> val;
        int pos = (1<<16) -1 + val;
        if (op == "add") {
            update(pos, 1);
        } else if (op == "del") {
            update(pos, -1);
        } else {  // op == "cnt"
            cout << cnt[val] << endl;
        }
    }
}
