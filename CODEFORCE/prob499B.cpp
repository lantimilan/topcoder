#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, string> mp;

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        string from, to; cin >> from >> to;
        mp[from] = to;
    }
    bool first = true;
    for (int i = 0; i < n; ++i) {
        string word; cin >> word;
        string target = mp[word];
        string output;
        if (target.length() < word.length()) {
            output = target;
        } else {
            output = word;
        }
        if (!first) cout << ' ';
        if (first) first = false;
        cout << output;
    }
    cout << endl;
}
