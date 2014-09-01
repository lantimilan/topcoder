// prob451A.cpp
//
// each move will reduce n and m by 1
// so number of moves is fixed, min(n,m), regardless of what moves each player take


#include <iostream>
using namespace std;

int main()
{
    int n, m; cin >> n >> m;
    n = min(n, m);
    string ans;
    if (n & 1) ans = "Akshat";
    else ans = "Malvika";

    cout << ans << endl;
}
