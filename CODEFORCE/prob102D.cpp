// prob102D.cpp
// http://codeforces.com/contest/102/problem/D
//
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

const int N=200000+5;
const int MOD=1000000000+7;
int dp[N];
int sum[N];

int main()
{
    int n,m; cin >> n >> m;
    vector<pii> buses(m);
    for(int i=0; i<m; ++i)
        cin >> buses[i].second>> buses[i].first; //(t[i],s[i])

    sort(buses.begin(), buses.end()); // sort by t[i]
    
    vector<int> pos; pos.push_back(0); pos.push_back(n);
    for(int i=0; i<m; ++i)
    {
        pos.push_back(buses[i].first);
        pos.push_back(buses[i].second);
    }
    sort(pos.begin(), pos.end());
    pos.resize(unique(pos.begin(),pos.end())-pos.begin());
    sum[0]=0; dp[0]=1; sum[1]=sum[0]+dp[0];
    int busid=0;
    for(int i=1; i<int(pos.size()); ++i)
    {
        dp[i]=0;
        for(; busid<m && buses[busid].first==pos[i]; ++busid)
        {
            int s = buses[busid].second;
            int spos = lower_bound(pos.begin(),pos.end(),s) - pos.begin();
            dp[i] = ((long long)dp[i]+sum[i]-sum[spos]+MOD)%MOD;
        }
        sum[i+1]=((long long)sum[i]+dp[i])%MOD;
    }
    //for(int i=0; i<int(pos.size()); ++i) cout << dp[i] << ' ' << sum[i] << endl;

    int last=int(pos.size())-1;
    int ans = dp[last];
    cout << ans << endl;
}

// let dp[p] be the number of ways to arrive pos[p], the ans is dp[n]
// dp[p] = sum over all bus[b] such that t[b]=p, and each summand is
// sum of dp[s[b]], dp[s[b]+1], ... dp[t[b]-1]
//
// However this takes O(m^2) time, which is 10^5^2=10^10, which is too slow
// Notice this summation is on a consecutive interval, so you can use prefix sum 
// to have O(1) per summation. Notice the indexing trick below.
//
// to this end we define sum[i+1]=sum[i]+dp[i] for all pos[i] with either
// pos[i]=s[b] or pos[i]=t[b] for some b
//
// then instead of summation, we can get the sum of dp[s[b]] to dp[t[b]-1] with
// O(1) time by sum[pos of t[b]] - sum[pos of s[b]]
//

