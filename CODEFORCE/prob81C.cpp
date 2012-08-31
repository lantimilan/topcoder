#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <utility>
using namespace std;

typedef vector<int> VI;
typedef pair<int,int> PII;

void solve()
{
    int n; cin >> n;
    int a, b; cin >> a >> b;
    VI scores(n);
    for(int i=0; i<n; ++i) { cin >> scores[i]; }

    priority_queue<PII> que;
    VI ans(n,0);
    if (a==b) { 
        int i;
        for(i=0; i<n/2; ++i) ans[i]=1;
        for(; i<n; ++i) ans[i]=2;
    }
    else if (a <= b) {
        for(int i=0; i<n; ++i)
        {
            int k = scores[i];
            PII p(k,n-i); que.push(p);
        }
        while(que.size() > b)
        {
            int k = n-que.top().second; que.pop();
            ans[k] = 1;
        }
        for(int i=0; i<n; ++i) if (ans[i]==0) ans[i] = 2;
    }
    else {
        for(int i=0; i<n; ++i)
        {
            int k = scores[i];
            PII p(k,i); que.push(p);
        }
        while(que.size() > a)
        {
            int k = que.top().second; que.pop();
            ans[k] = 2;
        }
        for(int i=0; i<n; ++i) if (ans[i]==0) ans[i] = 1;
    }

    for(int i=0; i<n; ++i)
    {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << endl;
}

int main()
{
    solve();
}
