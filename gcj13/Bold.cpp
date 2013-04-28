// greedy
//
// if E < R, set R = E
// now assume E >= R
// if E == R, then use all E every time
// else E > R
// use E only when at max v[i]
//
// all max v[i] must get E (first) or gap * R (other)

#include <iostream>
using namespace std;

typedef long long int64;

int val[10000+5];

void solve(int tcase)
{
    int E, R, N; cin >> E >> R >> N;
    for (int i = 0; i < N; ++i) cin >> val[i];

    int64 ans = 0;
    if (E < R) R = E;
    if (E == R) {
        for (int i = 0; i < N; ++i)
            ans += (int64)E * val[i];
    } else {
        int pos = 0;
        for (int i = 0; i < N; ++i)
            if (val[i] > val[pos]) pos = i;
        for (int i = 0; i < N; ++i)
            ans += (int64)R * val[i];
        ans += (int64)(E - R) * val[pos];
    }
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
