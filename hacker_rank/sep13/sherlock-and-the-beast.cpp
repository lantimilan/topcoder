// sherlock-and-the-beast.cpp
//
#include <iostream>
#include <cassert>
using namespace std;

void solve()
{
    int N; cin >> N;
    int three, five;
    for (three = 0; three <= N; three += 5) {  // must enter loop
        five = N - three;
        if (five % 3 == 0) break;
    }
    assert(three >= 0 && five >= 0);
    if (five % 3 != 0) { cout << -1 << endl; return; }
    string s3(three, '3');
    string s5(five, '5');
    cout << s5 + s3 << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}

// Accepted
