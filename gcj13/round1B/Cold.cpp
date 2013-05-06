// C.cpp

// read in dict, set<string>
//
// calc(int l, int r) returns
// min num of op to make S[l..r) words
// or -1 if impossible

#include <algorithm>
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int D = 5;
const int INF = -1;

vector<string> dict;
int dp[4005][6];
string S;
int N;

bool cmp(const string &s1, const string &s2)
{
    if (s1.length() != s2.length()) return s1.length() < s2.length();
    return s1 < s2;
}

int binsearch(int len)
{
    int lo = -1, hi = dict.size();
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (dict[m].length() < len) lo = m;
        else hi = m;
    }
    return hi;
}

int change(int l, int r, int c, int prev)
{
    string word = S.substr(l, r-l);
    int len = word.length();
    int ans = prev;

    int k = binsearch(len);
    assert(k >= dict.size() || dict[k].length() >= len);

    for (; k < dict.size(); ++k)
    {
        if (dict[k].length() > word.length()) break;
        int curr = 0;
        int p = prev;
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] != dict[k][i]) {
                if (p == N || l+i-p >= D) { curr++; p = i; }
                else { curr = INF; break; }

                if (curr > c) { curr = INF; break; }
            }
        }
        if (curr != INF) {
            if (ans == INF || (ans != N && ans > p)) ans = p;
        }
    }
    return ans;
}

int calc(int l, int r, int c, int prev)
{
    assert(l < r);
    if (dp[l][r][c][prev] != NOTUSED) return dp[l][r][c][prev];
    // one word
    int ans = change(l, r, c, prev);

    // split
    for (int k = l+1; k < r; ++k)
    for (int c1 = 0; c1 <= c; ++c1)
    {
        int p1, p2;
        p1 = p2 = INF;
        p1 = calc(l, k, c1, prev);
        if (p1 != INF) {
            p2 = calc(k, r, c-c1, p1);
        }
        if (p1 != INF && p2 != INF) {
            if (ans == INF || (ans != N && ans > p2)) ans = p2;
        }
    }
    return dp[l][r][c][prev] = ans;
}

void solve(int tcase)
{
    cin >> S;
    N = S.length();

    for (int l = 0; l < N; ++l)
    for (int r = l+1; r <= N; ++r)
    for (int c = 0; c < 11; ++c)
    for (int prev = 0; prev <= N; ++prev)
    {
        dp[l][r][c][prev] = NOTUSED;
    }

    int ans = N;
    for (int c = 0; c < 11; ++c)
    {
        if (calc(0, S.length(), c, N) != INF) { ans = c; break; }
    }
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

void init()
{
    ifstream fin("dict.txt");
    string w;
    while (fin >> w) {
        dict.push_back(w);
    }
    sort(dict.begin(), dict.end(), cmp);
    //cout << "dict " << dict.back().length() << endl;
}

int main()
{
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
