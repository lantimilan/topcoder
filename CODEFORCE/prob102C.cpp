#include <iostream>
#include <string>
using namespace std;

#define sz(a) int(a.size())

void solve()
{
    string s; cin >> s;
    int k; cin >> k;
    int cnt[30]={0};
    for(int i=0; i<sz(s); ++i)
        cnt[s[i]-'a']++;

    int sum=0;
    while(sum<k)
    {
        int x=-1;
        for(int i=0; i<26; ++i) if (cnt[i]>0)
        { if (x<0 || cnt[x] > cnt[i]) x=i; }
        if (x<0) break;
        if (sum+cnt[x] <= k) { sum += cnt[x]; cnt[x]=0; }
        else { sum=k; cnt[x] = 1; }
    }
    int m=0;
    for(int i=0; i<26; ++i) m+=(cnt[i]>0);
    cout << m << endl;

    string ans;
    for(int i=0; i<sz(s); ++i) if (cnt[s[i]-'a'])
        ans += s[i];

    cout << ans << endl;
}

int main()
{
    solve();
}
