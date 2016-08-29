// bon-appetit.cc
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    int share = 0;
    for (int i = 0; i < n; ++i) {
        int cost; cin >> cost;
        if (i == k) {
        } else {
            share += cost;
        }
    }
    int charged; cin >> charged;
    if (share == charged * 2) {
        cout << "Bon Appetit\n";
    } else {
        cout << charged - share / 2 << endl;
    }
}
