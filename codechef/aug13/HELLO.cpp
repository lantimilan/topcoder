// HELLO.cpp

// careful, floating point precision

#include <iostream>
#include <string>
using namespace std;

int str2int100(const string &s)
{
    int ans = 0;
    for (int i = 0; i < s.length(); ++i) if (s[i] != '.')
        ans = ans * 10 + s[i] - '0';
    return ans;
}

void solve()
{
    string s;
    int best;
    double cost;
    int unitcost, minutes, plans;
    cin >> s; unitcost = str2int100(s);
    cin >> minutes >> plans;
    cost = unitcost * minutes; best = 0;

    for (int p = 1; p <= plans; ++p) {
        int months; cin >> months;
        int rate;
        cin >> s; rate = str2int100(s);
        int curr = rate * minutes;
        int activate; cin >> activate;
        curr += 100.0 * activate / months;
        if (curr < cost) {
            cost = curr; best = p;
        }
    }

    cout << best << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}
