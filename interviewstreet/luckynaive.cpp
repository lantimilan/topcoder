// luckynaive.cpp
//
#include <cstdio>
using namespace std;

bool isprime(int n)
{
    if (n<2) return false;
    for(int k=2; k*k<=n; ++k) if (n%k==0) return false;
    return true;
}

int main()
{
    int n=100000;
    int ans=0;
    for(int i=1; i<n; ++i) {
        int sum=0, sqr=0;
        int d=i;
        while(d) {
            int dd=d%10;
            sum+=dd; sqr+=dd*dd;
            d/=10;
        }
        if (isprime(sum) && isprime(sqr)) ans++;
        printf("%d: %d\n", i, ans);
    }
}
