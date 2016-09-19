// combination-lock.cc
#include <algorithm>
#include <iostream>
using namespace std;

int a[5];
int b[5];

int sub(int x, int y) {
    if (x < y) swap(x, y);
    return min(x - y, 10 + y - x);
}

int main() {
    for (int i = 0; i < 5; ++i) cin >> a[i];
    for (int i = 0; i < 5; ++i) cin >> b[i];
    int cost = 0;
    for (int i = 0; i < 5; ++i) {
        cost += sub(a[i], b[i]);
    }
    cout << cost << endl;
}
