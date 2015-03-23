// prob527B.cpp

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int get_pos(const string &s1, char c1, const string &s2, char c2)
{
    for (int i = 0; i < s1.length(); ++i)
        if (s1[i] == c1 && s2[i] == c2) return i;
    return -1;
}

int main()
{
    int n; cin >> n;
    string S, T; cin >> S >> T;
    int mp[26][26]; memset(mp, 0, sizeof mp);
    int mismatch = 0;
    for (int i = 0; i < n; ++i) {
        char s = S[i], t = T[i];
        if (s != t) {
            mismatch++;
            mp[s - 'a'][t - 'a'] = 1;
        }
    }
    // swap to match two pos
    int p1, p2; p1 = p2 = -1;
    for (char s = 'a'; s <= 'z'; ++s)
    for (char t = 'a'; t <= 'z'; ++t) if (s != t)
    {
        if (mp[s-'a'][t-'a'] && mp[t-'a'][s-'a']) {
            p1 = 1 + get_pos(S, s, T, t);
            p2 = 1 + get_pos(S, t, T, s);
            break;
        }
    }
    if (p1 > 0) {
        cout << mismatch - 2 << endl;
        cout << p1 << ' ' << p2 << endl;
        return 0;
    }
    // swap to match one pos
    for (char s = 'a'; s <= 'z'; ++s)
    for (char t = 'a'; t <= 'z'; ++t) if (s != t) {
        if (mp[s-'a'][t-'a']) {
            bool found = false;
            for (char t2 = 'a'; t2 <= 'z'; ++t2) if (t != t2) {
                if (mp[t-'a'][t2-'a']) {
                    found = true;
                }
            }
            if (found) {
                p1 = 1 + get_pos(S, s, T, t);
                for (char t2 = 'a'; t2 <= 'z'; ++t2) if (t != t2) {
                    int p = get_pos(S, t, T, t2);
                    if (p >= 0) {
                        p2 = 1 + p; break;
                    }
                }
            }
        }
    }
    if (p1 > 0) {
        cout << mismatch - 1 << endl;
        cout << p1 << ' ' << p2 << endl;
        return 0;
    }

    cout << mismatch << endl;
    cout << p1 << ' ' << p2 << endl;
}
