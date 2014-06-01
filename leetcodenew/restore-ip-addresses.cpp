/**
* restore-ip-addresses.cpp
* https://oj.leetcode.com/problems/restore-ip-addresses/
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if (s.empty()) return vector<string>();
        int n = s.size();
        vector<vector<vector<string> > > dp(n+1);
        dp[1] = vector<vector<string> >(1, vector<string>(1, s.substr(0,1)));

        for (int i = 2; i <= n; ++i) {
            for (int k = 0; k < dp[i-1].size(); ++k) {
                // either extend last token, or append as a new token
                vector<string> cur = dp[i-1][k];
                string last = cur[cur.size()-1];
                string next = last + s[i-1];
                cur.push_back(string(1, s[i-1])); dp[i].push_back(cur);
                cur.pop_back();
                cout << cur.size() << endl;
                if (next[0] != '0')
                    if (next.length() < 3 || (next.length() == 3 && next <= "255")) {
                         cur.pop_back(); cur.push_back(next); dp[i].push_back(cur);
                    }
                cout << cur.size() << endl;
            }
        }
        vector<string> ip_address;
        for (int k = 0; k < dp[n].size(); ++k) {
            ip_address.push_back(join(dp[n][k], '.'));
        }
        return ip_address;
    }

    string join(const vector<string> &vs, char ch) {
        string ret = vs[0];
        for (int i = 1; i < vs.size(); ++i) {
            ret += string(1, ch) + vs[i];
        }
        return ret;
    }
};

int main()
{
    Solution sol;
    vector<string> ips = sol.restoreIpAddresses("25525511135");
    for (int i = 0; i < ips.size(); ++i) {
        cout << ips[i] << endl;
    }
}

// interesting: got output limit exceeded
// because the intended solution indicates an ip consists of 4 parts
// and OJ is kind enough to supply very long string and expect you
// to detect this by checking whether length <= 12 as the first thing
