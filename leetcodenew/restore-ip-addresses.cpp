/**
* restore-ip-addresses.cpp
* https://oj.leetcode.com/problems/restore-ip-addresses/
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * what is an ip address
 * 0 to 255
 * no leading zero
 */
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        // two issues in my previous implementation
        // 1. the intended solution is that you have to have exactly 4 parts for an ip address
        // 2. ip address has no leading zero except zero
        // 3. I forgot to return and got Segfault again!
        vector<string> ip_address;
        if (s.length() > 3 * 4) return ip_address;
        int n = s.size();
        int a[5];
        a[0] = 0; a[4] = n;
        for (a[1] = 1; a[1] < n; ++a[1])
        for (a[2] = a[1]+1; a[2] < n; ++a[2])
        for (a[3] = a[2]+1; a[3] < n; ++a[3]) {
            vector<string> vec;
            for (int i = 0; i < 4; ++i) vec.push_back(s.substr(a[i], a[i+1] - a[i]));
            // now check each parts
            // 1. length in 1,2,3
            // 2. val in 0 to 255
            // 3. no leading 0 if not zero
            bool good = true;
            for (int i = 0; i < 4; ++i) {
                string part = vec[i];
                int len = part.length();
                if (1 <= len && len <= 3) {
                    if (len > 1 && part[0] == '0') good = false;
                    if (len == 3 && part > "255") good = false;
                } else { good = false; }
            }
            if (good) {
                string ip = join(vec, '.');
                ip_address.push_back(ip);
            }
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
