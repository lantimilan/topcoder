// imba.cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> vec(n);
        int p = 0;
        for (int i = 1, j = n; i < j; i++, j--) {
            vec[p++] = j;
            vec[p++] = i;
        }
        if (n&1) vec[p] = n/2 + 1;
        reverse(vec.begin(), vec.end());
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << vec[i];
        }
        cout << endl;
    }
}
