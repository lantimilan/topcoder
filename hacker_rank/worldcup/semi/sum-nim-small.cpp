// sum-nim-small.cpp

#include <iostream>
#include <set>
#include <vector>
using namespace std;

set<vector<pair<int,int>>> st;

int main() {
    int N; cin >> N;
    int a[40];
    for (int i = 0; i < N; ++i) cin >> a[i];

    int ans = 0;
    for (int mask = 0; mask < (1<<(N-1)); ++mask) {
        vector<int> vec;
        int pos = 0;
        int fullmask = 1<< N-1 | mask;
        for (int i = 0; i < N; ++i) {
            if (fullmask & 1<<i) {
                int s = 0;
                for (int j = pos; j <= i; ++j) {
                    s += a[j];
                }
                vec.push_back(s);
                pos = i+1;
            }
        }

        int nim = 0;
        for (int elem : vec) {
            nim ^= elem;
        }
        if (nim == 0) {
            ans++;
        }
    }
    cout << ans << endl;
}

