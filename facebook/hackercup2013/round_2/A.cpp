// A.cpp

#include <iostream>
using namespace std;

int a[105];
int s[105];

void solve(int tcase)
{
    int N; cin >> N;
    for (int i=0; i<N; ++i) cin >> a[i];
    s[0] = 0;
    for (int i=0; i<N; ++i) s[i+1] = s[i] + a[i]+ 1 + max(0, a[i]-2);

    long long ans = 1;
    for (int i=0; i<N; ++i)
        ans += (a[i]+a[i]-1) * (s[i]+1) - a[i];
    cout << "Case #" << tcase << ": " << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}
