#include <cstdio>
#include <cstring>
using namespace std;

char s[100];
char t[100];

bool issqr(const char str[])
{
    int n=strlen(str);
    if (n&1) return false;
    for(int i=0, j=n/2; j<n; ++i, ++j)
        if (str[i]!=str[j]) return false;
    return true;
}

void solve()
{
    int n, ans;
    gets(s);
    n=strlen(s);
    ans=0;
    for(int b=1; b<1<<n; ++b) {
        int p=0;
        for(int i=0; i<n; ++i) if (b&1<<i) {
            t[p++]=s[i];
        }
        t[p]='\0';
        if (issqr(t)) { printf("%d: %s\n", b, t); ans++; }
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=0; t<T; ++t)
        solve();
}
