#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<string, string> mp;  // digit, word
set<string> st;  // digits

char table[] = {  // 'a' to 'z'
    '2', // 'a'
    '2', // 'b'
    '2', // 'c'
    '3', // 'd'
    '3', // 'e'
    '3', // 'f'
    '4', // 'g'
    '4', // 'h'
    '1', // 'i'
    '1', // 'j'
    '5', // 'k'
    '5', // 'l'
    '6', // 'm'
    '6', // 'n'
    '0', // 'o'
    '7', // 'p'
    '0', // 'q'
    '7', // 'r'
    '7', // 's'
    '8', // 't'
    '8', // 'u'
    '8', // 'v'
    '9', // 'w'
    '9', // 'x'
    '9', // 'y'
    '0', // 'z'
};

int main()
{
    string bad = "No solution.";

    string phone;
    int n;
    while (cin >> phone) {
        if (phone == "-1") break;
        cin >> n;
        mp.clear(); st.clear();
        for (int i=0; i<n; ++i) {
            string word; cin >> word;
            string digit = word;
            for (int x=0; x<word.length(); ++x) {
                digit[x] = table[word[x]-'a'];
            }
            mp[digit] = word;
            st.insert(digit);
        }
        int dp[105]; memset(dp, -1, sizeof dp);
        int pred[105];
        dp[0] = 0; pred[0] = 0;
        for (int pos=1; pos<=phone.length(); ++pos) {
            for (int prev=pos-1; prev>=0; --prev) {
                if (dp[prev]>=0 && st.count(phone.substr(prev, pos-prev))) {
                    if (dp[pos] < 0 || dp[pos] > dp[prev]+1) {
                        dp[pos] = dp[prev]+1;
                        pred[pos] = prev;
                    }
                }
            }
        }
        if (dp[phone.length()] < 0) cout << bad << endl;
        else {
            vector<string> ans;
            int p = phone.length(), q;
            while (p > 0) {
                q=p; p=pred[q];
                ans.push_back(mp[phone.substr(p,q-p)]);
            }
            bool first = true;
            for (int i=ans.size()-1; i>=0; --i) {
                if (!first) cout << ' ';
                first = false;
                cout << ans[i];
            }
            cout << endl;
        }
    }
}

// 4674599  23:45:19
// 13 Dec 2012 lantimilan  1002. Phone Numbers C++ Accepted
//   0.14    4 064 KB
