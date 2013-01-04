#include <iostream>
#include <map>
#include <utility>
using namespace std;

typedef long long int64;

const int64 MASK = (1LL<<32)-1;
typedef pair<int64, int64> frac;
typedef pair<frac, int64> mykey;

map<mykey, int64> memo;

int64 gcd(int64 m, int64 n)
{
    return n==0 ? m : gcd(n, m%n);
}

int64 calc(frac f, int64 L)
{
    cout << f.first << "/" << f.second << " " << L << endl;
    if (L==0) return frac(1,1) == f;
    if (memo.find(mykey(f, L)) != memo.end())
        return memo[mykey(f, L)];

    int64 &ans = memo[mykey(f, L)];
    ans = 0;
    int64 num = f.first;
    int64 deno = f.second;
    int64 g;
    for (int d=1; d<10; ++d) {
        if (L&1) {
            deno *= d;
            g = gcd(num, deno);
            num /= g; deno /= g;
            ans += calc(frac(num, deno), L-1);
        } else {
            num *= d;
            g = gcd(num, deno);
            num /= g; deno /= g;
            ans += calc(frac(num, deno), L-1);
        }
        ans &= MASK;
    }
    return ans;
}

// 0 needs to be handled specially
// any 0 in the digits will cause result to be 0
// but you cannot have d/0
int main()
{
    int T; cin >> T;
    //while (T--) {
    {
        int64 L, V; cin >> L >> V;
        frac f(V, 1);
        int64 ans = calc(f, L);
        cout << ans << endl;
    }
}
