// prob554A.cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    string s; cin >> s;
    int n = s.length();
    set<string> words;
    for (int p = 0; p <= n; ++p) {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            words.insert(s.substr(0, p) + ch + s.substr(p));
        }
    }
    cout << words.size() << endl;
}
