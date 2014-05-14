// A.cpp
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

long long gcd(long long a, long long b)
{
    if (b == 0) return a;
    else return gcd(b, a % b);
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    string s; cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '/') s[i] = ' ';
    }
    istringstream iss(s);
    long long P, Q; iss >> P >> Q;
    long long g = gcd(P, Q);
    P /= g; Q /= g;
    if (Q & Q-1) {
        cout << "impossible" << endl;
        return;
    }
    int ans = 0;
    while (P < Q) {
        ans++;
        Q >>= 1;
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
