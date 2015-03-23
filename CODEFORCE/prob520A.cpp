// prob520A.cpp
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n; cin >> n;
    string s; cin >> s;
    bool letter[26] = {0};
    for (int i = 0; i < s.length(); ++i) {
        char ch = tolower(s[i]);
        letter[ch - 'a'] = 1;
    }
    bool good = true;
    for (int c = 0; c < 26; ++c) {
        if (!letter[c]) good = false;
    }
    cout << (good ? "YES" : "NO") << endl;
}
