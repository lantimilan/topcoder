// let f(n) be number of sequence with length n and first != last
// g(n) be number of sequence with length n with fist == last
//
// g(2) = 0
//
// f(1) = 1
// f(2) = 3
// f(3) = 2*f(2) + 3*g(2)
//
// we have f(n) = 2*f(n-1) + 3*g(n-1)
// and g(n) = f(n-1)
// ans is 4*f(n) for begin with a,b,c,d
//
// (f[n]+f[n-1]) = 3(f[n-1] + f[n-2])
// but how do you solve f[n]?

#include <cstdio>
using namespace std;

const int MOD = 1000000000+7;

typedef long long int64;

int mult(int a, int b)
{
    return (int64)a*b %MOD;
}

int fastpow(int a, int n)
{
    int ans=1;
    int f = a;
    while(n) {
        if (n&1) ans = mult(ans, f);
        f = mult(f, f);
        n/=2;
    }
    return ans;
}

int main()
{
    int T; scanf("%d", &T);   
    while(T--) {
        int N; scanf("%d", &N);
        // from oeis
        // 3^n + (-1)^n * 3
        // search 6, 21, 60
        int ans;
        ans = fastpow(3,N);
        if (N&1) ans -=3;
        else ans = (ans+3)%MOD;

        if (ans<0) ans+=MOD;
        printf("%d\n", ans);
    }
}

// Correct Answer
// Execution Time: 0.03
