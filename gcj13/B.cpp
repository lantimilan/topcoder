// greedy
//
// if E < R, set R = E
// now assume E >= R
// if E == R, then use all E every time
// else E > R
// use E only when at max v[i]
//
// all max v[i] must get E (first) or gap * R (other)
//
// int64 calc(int begin, int end, int level)  // profit of [begin, end) with a[end] must be level
// not working ??
// is it implementation fault or algorithm wrong? implementation wrong

#include <iostream>
using namespace std;

typedef long long int64;

int64 E, R, N;
int val[10000+5];
int need[10000+5];

int64 calc(int begin, int end, int64 level)
{
    if (begin >= end) return 0;
    int pos = begin - 1;
    for (int i = begin; i < end; ++i) if (pos < begin || val[i] > val[pos]) pos = i;
    int64 cap;
    if (begin == 0) cap = E;
    else {
        cap = min(E, R * (pos+1 - begin));  // careful here, only accumulate from begin-1 to pos-1
    }
    for (int i = pos-1, sub = cap-R; i >= begin && sub > 0; --i, sub -= R)
        need[i] = max(need[i], sub);
    int64 curr = val[pos] * (cap - need[pos]);
    if (curr < 0) curr = 0;  // careful here, no gain but not negative
    //cout << "calc " << begin << ' ' << end << ' ' << level << ' ' << curr << ' ' << need[pos] << endl;
    return calc(begin, pos, cap) + curr + calc(pos+1, end, level);
}

void solve(int tcase)
{
    cin >> E >> R >> N;
    for (int i = 0; i < N; ++i) cin >> val[i];
    for (int i = 0; i < N; ++i) need[i] = 0;

    int64 ans = calc(0, N, 0);
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
