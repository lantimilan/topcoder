// memsqlA.cpp

#include <iostream>
#include <string>
using namespace std;

bool match(string actual, string patt)
{
    if (actual.length() != patt.length()) return false;
    for (int i = 0; i < patt.length(); ++i) {
        if (patt[i] == '.' || actual[i] == patt[i]) {}
        else return false;
    }
    return true;
}

int main()
{
    string words[] = {"vaporeon", "jolteon", "flareon", "espeon",
        "umbreon", "leafeon", "glaceon", "sylveon"};
    int n; cin >> n;
    string target; cin >> target;
    string ans;
    for (int i = 0; i < 8; ++i) {
        if (match(words[i], target)) {
            ans = words[i]; break;
        }
    }
    cout << ans << endl;
}
