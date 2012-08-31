#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

void solve()
{
    int n, m; cin >> n >> m;
    int price[105];
    for(int i=0; i<n; ++i) cin >> price[i];

    set<pair<int,int> > edges;
    for(int i=0; i<m; ++i)
    {
        int u,v; cin >> u >> v; u--; v--;
        edges.insert(make_pair(u,v));
        edges.insert(make_pair(v,u));
    }
    const int MAX = 100000000;
    int ans=MAX;
    for(int a=0; a<n; ++a)
    for(int b=a+1; b<n; ++b)
    for(int c=b+1; c<n; ++c)
    {
        int sum = price[a]+price[b]+price[c];
        if (edges.count(make_pair(a,b)) &&
            edges.count(make_pair(b,c)) &&
            edges.count(make_pair(c,a)))
        ans = min(ans, sum);
    }
    if (ans >= MAX) ans=-1;
    cout << ans << endl;
}
int main()
{
    solve();
}
