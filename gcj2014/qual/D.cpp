// D.cpp
//
// War: # capture by Ken on Naomi
// Deceibt War: # capture by Naomi on Ken

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int capture(vector<int> a, vector<int> b)
{
    int N = a.size();
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int cnt = 0;
    int apos, bpos; apos = bpos = N-1;
    for (; apos >= 0; --apos) {
        while (bpos >= 0 && a[apos] < b[bpos]) {
            bpos--;
        }
        if (bpos < 0) break;
        cnt++; bpos--;  // apos captures bpos
    }
    return cnt;
}

int read_int()
{
    string s; cin >> s;
    s = s.substr(2);
    istringstream iss(s);
    int val; iss >> val;
    return val;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N; cin >> N;
    vector<int> Naomi(N), Ken(N);
    for (int i = 0; i < N; ++i) Naomi[i] = read_int();
    for (int i = 0; i < N; ++i) Ken[i] = read_int();
    int war_score = N - capture(Ken, Naomi);
    int deceipt_score = capture(Naomi, Ken);
    cout << deceipt_score << ' ' << war_score << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}

