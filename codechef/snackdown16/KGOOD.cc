// KGOOD.cc
//
// cnt[26]
// let min be the min > 0
// then all others need to be at most min + K
// you can also remove all occurrence of a certain letter
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

string s;
int main() {
    int T; cin >> T;
    while (T--) {
        cin >> s;
        int lim; cin >> lim;
        int cnt[26] = {0};
        for (char ch : s) {
            cnt[ch - 'a']++;
        }
        vector<int> v;
        for (int i = 0; i < 26; ++i) if (cnt[i]) {
            v.push_back(cnt[i]);
        }
        sort(v.begin(), v.end());

        int best = s.length();  // we may remove all letters
        // consider remove [0..begin) and keep [begin..len)
        for (int begin = 0; begin < v.size(); ++begin) {
            int ans = 0;
            for (int i = 0; i < begin; ++i) {
                ans += v[i];
            }
            int base = v[begin];
            for (int i = begin; i < v.size(); ++i) {
                int k = v[i];
                if (k > base + lim) {
                    ans += (k - base - lim);
                }
            }
            best = min(best, ans);
        }
        cout << best << endl;
    }
}
// Accepted
// WA, why?
// you can remove all occurrence of a single letter
