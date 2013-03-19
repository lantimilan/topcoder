// zipfsong.cpp
//
// spotify puzzle: zipfsong
//

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef long long int64;

pair<int64, int> songs[50000+5];
string names[50000+5];

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int64 freq;
        string name;
        cin >> freq >> name;
        songs[i] = make_pair(-freq * (i+1), i);
        names[i] = name;
    }
    sort(songs, songs+n);
    for (int i = 0; i < m; ++i) {
        cout << names[songs[i].second] << endl;
    }
}
