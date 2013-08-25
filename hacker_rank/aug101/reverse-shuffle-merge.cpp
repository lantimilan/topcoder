// reverse-shuffle-merge.cpp
//
// count a to z

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string s; cin >> s; reverse(s.begin(), s.end());
    int cnt[30] = {0};

    for (int i = 0; i < s.length(); ++i) {
        int x = s[i] - 'a';
        cnt[x]++;
    }

    for (int x = 0; x < 26; ++x) {
        assert(cnt[x] % 2 == 0);
        cnt[x] /= 2;
    }

    int me[30] = {0};
    int other[30] = {0};

    // look for min ch
    // invariant: there is a valid substr in s[i..s.length()-1]
    string ans(s.length()/2, ' ');
    int pos = 0;
    for (int i = 0; i < s.length(); ) {
        char targ = 'z'+1;
        int targpos = i-1;  // targpos is the next pos for me[]
        int j;
        for (j = i; j < s.length(); ++j) {  // search targ from i to j, range starts at i and stops at other[] has absorbed enough
            int x = s[j] - 'a';
            if (targ > s[j] && me[x] < cnt[x]) { targ = s[j]; targpos = j; }
            if (other[x] + 1 > cnt[x]) break;
            other[x]++;
            //cout << "other " << char(x+'a') << ' ' << other[x] << endl;
        }
        // post: other[] has incr from s[i..j-1] and all other[] are valid
        // either j == s.length() or s[j] cause other[s[j]] to exceed cnt[s[j]]
        ans[pos++] = targ; me[targ-'a']++;
        // remove counts from j-1 to targpos
        for (int k = j-1; k >= targpos; --k) { other[s[k]-'a']--; } // cout << "loop k " << s[k] << ' ' << other[s[k]-'a'] << endl; }
        //cout << "targpos " << targpos << ' ' << i << endl;
        //cout << targ << ' ' << me[targ - 'a'] << endl;
        i = targpos + 1;
        if (pos >= ans.length()) break;
    }

    cout << ans << endl;
}
