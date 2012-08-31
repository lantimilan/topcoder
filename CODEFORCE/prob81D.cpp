#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

typedef vector<int> VI;
typedef pair<int,int> PII;

void solve()
{
    int n, m; cin >> n >> m;
    VI a(m); for(int i=0; i<m; ++i) cin >> a[i];
    VI b(m);
    int sum = n;
    while(sum) {
        int minval=0, cnt=0;
        for(int i=0; i<m; ++i) if (a[i]>0)
        { cnt++; if (minval==0||a[i]<minval) minval=a[i]; }

        if (minval==0) break;

        if (sum/cnt==0) {
            for(int i=0; i<m; ++i) if (a[i]>0)
            { a[i]--; b[i]++; sum--; if (sum==0) break;}
        }
        else {
            int decr = min(sum/cnt, minval);
            for(int i=0; i<m; ++i) if (a[i]>0)
            { a[i]-=decr; b[i]+=decr; sum-=decr; }
        }
    }
    if (sum >0) { cout << -1 << endl; return; }
    int maxval=0,total=0;
    for(int i=0; i<m; ++i)
    { maxval = max(maxval, b[i]); total += b[i]; }
    if (maxval > total-maxval) { cout << -1 << endl; return; }

    vector<PII> avail;
    for(int i=0; i<m; ++i) if (b[i]) avail.push_back(PII(b[i],i));
    sort(avail.begin(), avail.end()); reverse(avail.begin(), avail.end());
    VI ans;
    while(avail[0].first) {
        for(int x=0; x<int(avail.size()) && avail[x].first; ++x)
        {
            int pp = (avail[x].second+1); ans.push_back(pp);
            avail[x].first--;
        }
    }
    int kk = ans.size(); 
    while(ans[kk-1]==ans[0])
    {
        for(int i=1; i<kk; ++i) if (ans[i]!=ans[0]&&ans[i-1]!=ans[0])
        {
            VI tmp=ans;
            for(int j=i; j<kk-1; ++j) tmp[j+1] = ans[j];
            tmp[i] = ans[kk-1];
            ans = tmp;
            break;
        }
    }
    cout << ans[0];
    for(int i=1; i<kk; ++i) cout << " " << ans[i];
    cout << endl;
}

int main()
{
    solve();
}
