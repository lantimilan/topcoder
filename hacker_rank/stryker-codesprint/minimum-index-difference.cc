// minimum-index-difference.cc
#include <iostream>
#include <map>
using namespace std;

int main() {
    int n; cin >> n;
    map<int, int> m1, m2;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        m1[k] = i;
    }
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        m2[k] = i;
    }
    int diff = n+1;
    int val = -1;
    for (const auto& p : m1) {
        int k = p.first;
        int pos = p.second;
        int d = abs(pos - m2[k]);
        if (d < diff) {
            diff = d;
            val = k;
        }
    }
    cout << val << endl;
}
