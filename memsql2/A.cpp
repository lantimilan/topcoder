// A.cpp

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s; cin >> s;
    int len = s.length();
    int n; cin >> n;
    int cnt[30] = {0};
    int avail[30] = {0};

    for (int i = 0; i < len; ++i) cnt[s[i]-'a']++;

    int used = 0;
    for (int c = 0; c < 26; ++c) if (cnt[c] > 0) {
        avail[c] = 1; used++;
    }
    if (used > n) {
        cout << -1 << endl;
        return 0;
    }

    while (used < n) {
        // find max need
        int a, b; a = b = 1;
        int up = -1;
        for (int c = 0; c < 26; ++c) if (cnt[c] > 0) {
            if (cnt[c] * b > avail[c] * a) {
                a = cnt[c]; b = avail[c]; up = c;
            }
        }
        if (up < 0) break;
        if (cnt[up] <= avail[up]) break;
        avail[up]++;
        used++;
    }
    int need = 0;
    for (int c = 0; c < 26; ++c) if (cnt[c] > 0) {
        int curr = (cnt[c] + avail[c]-1) / avail[c];
        need = max(need, curr);
    }
    cout << need << endl;
    string sheet;
    for (char ch = 'a'; ch <= 'z'; ++ch) if (cnt[ch-'a'] > 0) {
        string tmp(avail[ch-'a'], ch);
        sheet += tmp;
    }
    while (sheet.length() < n) sheet += 'a';
    cout << sheet << endl;
}
