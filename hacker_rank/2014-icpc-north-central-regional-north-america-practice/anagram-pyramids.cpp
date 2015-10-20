// anagram-pyramids.cpp
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int N, M;
string words[1000000+5];
map<string, int> lookup;
vector<int> adj[1000000+5];

bool cmp(const string &s1, const string &s2) {
    if (s1.length() != s2.length()) return s1.length() < s2.length();
    return s1 < s2;
}

void sanitize(string &s) {
    for (int i = 0; i < s.length(); ++i) {
        s[i] = toupper(s[i]);
    }
    sort(s.begin(), s.end());
}

bool dfs(int start, int target) {  // DAG, no cycle, might be too slow
    if (start == target) return true;
    for (int next : adj[start]) {
        if (dfs(next, target)) return true;
    }
    return false;
}

void solve(int tcase) {
    lookup.clear();
    for (int i = 0; i < N; ++i) adj[i].clear();

    for (int i = 0; i < N; ++i) {
        string word; cin >> word; sanitize(word);
        words[i] = word;
        lookup[word] = i;
    }
    sort(words, words + N, cmp);

    for (int i = 0; i < N; ++i) {
        string w = words[i];
        int from = lookup[w];
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            string next = w + ch; sanitize(next);
            if (lookup.count(next)) {
                int j = lookup[next];
                adj[from].push_back(j);
            }
        }
    }

    cout << "Case " << tcase << ":"; cout << endl;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        string s1, s2;
        cin >> s1 >> s2; //cout << s1 << ' ' << s2 << endl;
        sanitize(s1); sanitize(s2);
        if (!lookup.count(s1) || !lookup.count(s2)) {
            cout << "no" << endl;
            continue;
        }
        int first, last;
        first = lookup[s1];
        last = lookup[s2];
        cout << (dfs(first, last) ? "yes" : "no") << endl;
    }
}

int main() {
    int tcase = 0;
    while (cin >> N) {
        solve(++tcase);
    }
}
