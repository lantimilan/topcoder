// facilities-extraction.cpp
#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <utility>
using namespace std;

vector<pair<string,string>> facs;
set<string> st;
string text;

string tolower(const string &s) {
    string s2 = s;
    int n = s2.length();
    for (int i = 0; i < n; ++i) s2[i] = tolower(s2[i]);
    return s2;
}

bool is_prefix(const string &s1, const string &s2) {
    if (s1.length() > s2.length()) return false;
    for (int i = 0; i < s1.length(); ++i) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

int main() {
    int N; cin >> N; cin.ignore();
    facs.resize(N);
    for (int i = 0; i < N; ++i) {
        string fac; getline(cin, fac);
        facs[i] = make_pair(tolower(fac), fac);
    }
    getline(cin, text); text += string(30, ' ');
    int l = text.length();
    const int K = 30;
    for (int i = 0; i + K < l; ++i) {
        string s = text.substr(i, K);
        st.insert(tolower(s));
    }
    // question: are facilities in lower case already?
    vector<string> ans;
    for (int i = 0; i < N; ++i) {
        string target = facs[i].first;
        string s = *(st.lower_bound(target));
        if (is_prefix(target, s)) {
            ans.push_back(facs[i].second);
        }
    }
    sort(ans.begin(), ans.end());
    for (auto &s : ans) {
        cout << s << endl;
    }
}
