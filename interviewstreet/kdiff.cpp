// k difference
#include <cassert>
#include <cstdio>
#include <set>
using namespace std;

set<long long> numset;
long long a[100000+5];
int N, K;

int main()
{
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i) {
        scanf("%lld", &a[i]);
        numset.insert(a[i]);
    }
    
    long long ans=0;
    for(int i=0; i<N; ++i) {        
        if (numset.count(a[i]+K)) ++ans;
        if (numset.count(a[i]-K)) ++ans;
    }
    assert(ans%2==0);
    printf("%lld\n", ans/2);
}
