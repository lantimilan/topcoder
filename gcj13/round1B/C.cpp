// C.cpp

// use char[][] takes 1m44s
// use vector<string> takes 14m
// 10 times difference
//
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

const int D = 5;
const int INF = -1;

//vector<string> dict;
const int SZ = 521196;
char dict[521200][12];
int LEN[521200];
int dp[4005][6];
//string S;
char S[4005];
int N;

bool cmp(const string &s1, const string &s2)
{
    int n1 = s1.length(), n2 = s2.length();
    if (n1 != n2) return n1 < n2;
    return s1 < s2;
}

void update(int &a, int b)
{
    if (b != INF) {
        if (a == INF || a > b)
            a = b;
    }
}

void solve(int tcase)
{
    //cin >> S;
    //N = S.length();
    fgets(S, 4096, stdin);
    N = strlen(S);
    S[N-1] = '\0';
    N--;

    memset(dp, -1, sizeof dp);
    dp[0][5] = 0;

    for (int i = 1; i <= N; ++i)
//    for (int w = 0; w < dict.size(); ++w) {
    for (int w = 0; w < SZ; ++w) {
        //string word = dict[w];
        //int len = dict[w].length();
        const char *word = dict[w];
        //int len = strlen(word);
        int len = LEN[w];
        if (len > i) continue;

        bool good = true;
        int cnt = 0;
        int first = -1, prev = -1, last = -1;
        for (int p = 0; p < len; ++p) if (S[i-len+p] != word[p]) {
            ++cnt; last = p;
            if (first < 0) first = p;
            if (prev < 0) prev = p;
            else if (p - prev < D) { good = false; break; }
            else prev = p;
        }
        if (!good) continue;
        if (first < 0) {
            for (int p = 1; p <= 5; ++p) {
                int k = min(D, p+len);
                if (dp[i-len][p] != INF) {
                    int val = dp[i-len][p] + cnt;
                    if (dp[i][k] == INF || dp[i][k] > val)
                        dp[i][k] = val;
                    //update(dp[i][k], dp[i-len][p] + cnt);
                }
            }
        } else {
            int k = min(D, len - last);
            for (int p = 1; p <= 5; ++p) if (p + first >= D)
                if (dp[i-len][p] != INF) {
                    int val = dp[i-len][p] + cnt;
                    if (dp[i][k] == INF || dp[i][k] > val)
                        dp[i][k] = val;
                    //update(dp[i][k], dp[i-len][p] + cnt);
                }
        }
    }
    int ans = INF;
    for (int p = 1; p <= 5; ++p) {
        if (dp[N][p] != INF)
            update(ans, dp[N][p]);
    }
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

void init()
{
    //ifstream fin("dict.txt");
    FILE* fin = fopen("dict.txt", "r");
    //string w;
    //while (fin >> w) {
    //    dict.push_back(w);
    //}
    //sort(dict.begin(), dict.end(), cmp);
    //cerr << "dict " << dict.size() << endl;
    for (int i = 0; i < SZ; ++i) {
        fgets(dict[i], 1024, fin);
        int len = strlen(dict[i]);
        LEN[i] = len-1;
        dict[i][len-1] = '\0';
    }
    fclose(fin);
}

int main()
{
    init();
    int T; //cin >> T;
    scanf("%d ", &T);
    for (int t = 1; t <= T; ++t)
        solve(t);
}
