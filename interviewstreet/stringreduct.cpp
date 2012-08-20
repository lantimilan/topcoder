// string reduction
// AC
//
// some proof
//
// Claim:
// only one type of char will remain, the other two will be eliminated
//
// Algorithm:
// 1. count type of char, if only 1 type, then ans=n
// 2. do update until no update can be done, then the string will be ababa or
// ababab
// 3. update 1: remove all even block
// 4. update 2: remove all abc block
//
// 5. now we have only ababa or ababab or abab
// every abab can be reduced into cc and then can be removed if there are still
// other a or b. If none then ans=2. Otherwise we are left with a or ab or aba,
// all three can be reduced into 1 char so ans=1.
//
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

void solve()
{
    char s[105];
    gets(s); //puts(s);
    int n=strlen(s);
    if (n==0) { printf("0\n"); return; }
    int ans=n;

    bool same=true;
    char ch=s[0];
    for(int i=1; i<n; ++i) {
        if (s[i]!=ch) { same=false; break; }
    }
    if (same) { printf("%d\n", ans); return; }

    while(1) {
        bool update = false;
        char snew[105]={0};
        n=strlen(s);
        // remove even block
        for(int i=0, j=0; i<n; ) {
            if (i+1<n && s[i]==s[i+1]) { 
                i+=2; update=true;
            }
            else {
                snew[j++] = s[i++];
            }
        }
        memcpy(s, snew, sizeof s); //puts(s);
        memset(snew, 0, sizeof snew);
        // remove abc
        n=strlen(s);
        for(int i=0,j=0; i<n; ) {
            if (i+2<n && s[i]!=s[i+1] && s[i]!=s[i+2] && s[i+1]!=s[i+2]) {
                i+=3; update=true;
            }
            else {
                snew[j++] = s[i++];
            }
        }
        memcpy(s, snew, sizeof s); //puts(s);
        memset(snew, 0, sizeof snew);

        if (!update) break;
    }
    if (strlen(s)%4 == 0) ans=2;
    else ans=1;
    printf("%d\n", ans);
}
int main()
{
    int T; scanf("%d ", &T);
    for(int i=0; i<T; ++i)
        solve();
}
