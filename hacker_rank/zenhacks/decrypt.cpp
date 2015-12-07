// decrypt.cpp
#include <iostream>
#include <string>
using namespace std;

void solve() {
    string plain, enc; cin >> plain >> enc;
    int best = plain.length();
    for (int s = 0; s < 26; ++s) {
        int n = plain.length();
        string enc1 = plain;
        for (int p = 0; p < n; ++p) {
            int ch = plain[p];
            ch = ((ch - 'a') + s) % 26 + 'a';
            enc1[p] = ch;
        }
        int cnt = 0;
        for (int p = 0; p < n; ++p) {
            cnt += (enc1[p] != enc[p]);
        }
        best = min(best, cnt);
    }
    cout << best << endl;
}

int main() {
    int T; cin >> T;
    while(T--) {
        solve();
    }
}
