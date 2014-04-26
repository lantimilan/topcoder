// A.cpp
//

#include <iostream>
#include <vector>
using namespace std;

void solve(int tcase)
{
    int card1[4][4];
    int card2[4][4];

    int row1, row2;

    cin >> row1;
    for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
        cin >> card1[i][j];
    cin >> row2;
    for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
        cin >> card2[i][j];

    vector<int> v1(4), v2(4);
    for (int j = 0; j < 4; ++j) {
        v1[j] = card1[row1-1][j];
        v2[j] = card2[row2-1][j];
    }
    int ans = 0;
    int val = 0;
    for (int v = 1; v <= 16; ++v) {
        int cnt = 0;
        for (int j = 0; j < 4; ++j) {
            if (v1[j] == v) cnt++;
            if (v2[j] == v) cnt++;
        }
        if (cnt == 2) {
            val = v;
            ans++;
        }
    }
    cout << "Case #" << tcase << ": ";
    if (ans == 1) cout << val << endl;
    else if (ans == 0) cout << "Volunteer cheated!" << endl;
    else cout << "Bad magician!" << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
