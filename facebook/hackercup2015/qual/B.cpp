// B.cpp
#include <iostream>
using namespace std;

void solve(int tcase)
{
    int P, C, F; cin >> P >> C >> F;
    int N; cin >> N;
    int protein[25], carb[25], fat[25];
    for (int i = 0; i < N; ++i)
        cin >> protein[i] >> carb[i] >> fat[i];

    bool ans = false;
    for (int mask = 0; mask < (1<<N); ++mask) {
        int pp = 0, cc = 0, ff = 0;
        for (int i = 0; i < N; ++i) if (mask & 1 << i) {
            pp += protein[i];
            cc += carb[i];
            ff += fat[i];
        }
        if (pp == P && cc == C && ff == F) {
            ans = true;
        }
    }
    cout << "Case #" << tcase << ": ";
    if (ans) cout << "yes" << endl;
    else cout << "no" << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
