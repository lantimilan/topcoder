// prob552E.cpp
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// CF does not support std::to_string
// this is an easy E problem, because * is at most 15, and results fit in
// long long.

void update(long long &a, long long b) {
    if (a < b) a = b;
}

long long get_arg(int &pos, int end, const string &s) {
    long long x = 0;
    while (pos < end && isdigit(s[pos])) {
        x = 10 * x + s[pos++] - '0';
    }
    return x;
}

long long eval(const string &s, int begin, int end) {
    stack<long long> args;
    for (int i = begin; i < end; ) {
        if (s[i] == '*') {
            ++i;
            long long x = get_arg(i, end, s);
            x *= args.top(); args.pop();
            args.push(x);
        } else if (s[i] == '+') {
            ++i; // skip
        } else {
            args.push(get_arg(i, end, s));
        }
    }
    long long ans = 0;
    while (!args.empty()) {
        ans += args.top(); args.pop();
    }
    return ans;
}

string ll2string(long long x) {
    string s;
    do {
        s += char(x % 10 + '0');
        x /= 10;
    } while (x);
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    string s; cin >> s;
    vector<int> mpos; mpos.push_back(-1);

    int n = s.length();
    for (int i = 0; i < n; ++i) if (s[i] == '*') mpos.push_back(i);
    mpos.push_back(n);

    long long best = 0;
    for (int p = 0; p < mpos.size(); ++p)
        for (int q = p+1; q < mpos.size(); ++q) {
            int pp = mpos[p];
            int qq = mpos[q];
            long long mid = eval(s, pp+1, qq);
            string ss = s.substr(0, pp+1);
            //ss += to_string(mid);
            ss += ll2string(mid);
            ss += s.substr(qq, n - qq);
            //cout << mid << ' ' << ss << endl;
            long long curr = eval(ss, 0, ss.length());
            //cout << curr << endl;
            update(best, curr);
        }
    cout << best << endl;
}
