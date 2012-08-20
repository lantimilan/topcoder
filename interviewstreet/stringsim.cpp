// string similarity
// 
// AC
//
// Knuth-Morris-Pratt
//
// j=q[i];
// pref[i-j+1] = max(., j)
//
// k is left marker with k<=i and pref[k]>=i-k+1
// pref[i] = min(pref[i-k], pref[k]-(i-k))
//
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

void solve()
{
    char s[100000+5]; gets(s);
    int q[100000+5];
    int p[100000+5]={0};
    q[0]=0;
    int n=strlen(s);
    for(int i=1; i<n; ++i) {
        int k=q[i-1];
        while(k && s[k] != s[i]) k = q[k-1];
        if (k) q[i]=k+1;
        else {
            if (s[0]==s[i]) q[i]=1;
            else q[i]=0;
        }
    }
    //for(int i=0; i<n; ++i) printf("%d ", q[i]); puts("");

    for(int i=1; i<n; ++i) {
        int j=q[i];
        p[i-j+1]=max(p[i-j+1], j);
    }
    //for(int i=0; i<n; ++i) printf("%d ", p[i]); puts("");

    for(int i=1, k=1; i<n; ++i) 
        if (p[i]==0) {
            while(k<=i && p[k]<i-k+1) ++k;
            if (k>i) continue;
            else p[i]=min(p[i-k], p[k]-(i-k));
        }
        else {
            k=i;
        }
    //for(int i=0; i<n; ++i) printf("%d ", p[i]); puts("");
    
    long long ans=n;
    for(int i=1; i<n; ++i) ans+=p[i];
    printf("%lld\n", ans);
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=0; t<T; ++t)
        solve();
}
