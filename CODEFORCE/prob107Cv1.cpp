// http://codeforces.com/contest/107/problem/C
//
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

LL dp[1<<20];
int pred[20];

int bitcnt(int n)
{
    int ans=0;
    while(n) { n&=n-1; ++ans; }
    return ans;
}

// when counting, we put elem into pos in the order of elem
//
LL calc(int elem, int n, int taken, int prof[]) // prof[elem]=pos
{
    if (elem>=n) return 1LL;
    if (dp[taken]>=0) return dp[taken];

    LL &ans=dp[taken]; ans=0LL;
    if (prof[elem]>=0) { 
        int p=prof[elem];
        if ((1<<p & taken)==0 && (taken&pred[p]) == pred[p])
            ans += calc(elem+1, n, taken|1<<p, prof);
    }
    else {
        for(int p=0; p<n; ++p) 
        if ((1<<p & taken)==0 && (taken&pred[p])==pred[p])
        { // pos already taken must cover all pred[pos]
            ans += calc(elem+1, n, taken|1<<p, prof);
        }
    }
    return ans;
}

int main()
{
    int n,m; LL y;
    cin >> n >> y >> m;

    for(int i=0; i<m; ++i)
    {
        int a,b; cin >> a >> b;
        --a; --b;
        pred[b] |= 1<<a;
    }

    int seat[20]; for(int i=0; i<n; ++i) seat[i]=-1; // seat[pos]=prof
    int ans[20]; for(int i=0; i<n; ++i) ans[i]=-1; // ans[prof]=pos
    y-=2000;
    LL cnt=0;
    int used=0; // set of prof placed in prefix

    // for each pos=0 to n-1
    // try to put prof 0 to n-1 at current pos
    for(int pos=0; pos<n; ++pos)
    {
    int elem;
    for(elem=0; elem<n; ++elem) if (ans[elem]==-1)
    {
        memset(dp,-1,sizeof dp);
        ans[elem]=pos;
        cnt = calc(0,n,0,ans); // (elem,n,taken,ans[]) #perms after fix prof at 0..pos

    //cout << pos+1 << ' ' << elem+1 << ' ' << cnt << ' ' << y << endl;
        if (cnt>=y) { seat[pos]=elem; used |= 1<<elem; break; }
        else { y-=cnt; ans[elem]=-1; }
    }
    if (elem>=n) { cout << "The times have changed" << endl; return 0; }
    }
    /*
    if (ans[pos]==-1 && ((used&pred[pos])==pred[pos])) 
    // pos not used and used covered all pred[pos]
    {
    cout << elem << ' ' << pos << ' ' << y << endl;
        ans[pos]=elem;
        used |= 1<<pos;
        memset(dp,0,sizeof dp);
        dp[used]=1LL;
        for(int s=1; s<(1<<n); ++s) if ((s&used)==used)
        for(int i=elem+1; i<n; ++i)
        for(int p=0; p<n; ++p) if (ans[p]==-1)
        {
            // s has p and s has all pred[p]
            if ((s&(1<<p)) && (s&pred[p])== pred[p])
            {
                dp[s] += dp[s^(1<<p)];
            }
        } // end i=elem+1 to n-1
        if (dp[(1<<n)-1]>=y) break;
        else { y-=dp[(1<<n)-1]; ans[pos]=-1; used &= ~(1<<pos); }
    }
    cout << "elem " << elem << ' ' << dp[(1<<n)-1] << endl;
    }
    y-=dp[(1<<n)-1];
    */
    y-=cnt;
    if (y>0) cout << "The times have changed" << endl;
    else {
        for(int i=0; i<n; ++i)
        {
            if (i) cout << ' ';
            cout << seat[i]+1;
        }
        cout << endl;
    }
}

//666593   Sep 4, 2011 3:25:35 AM  lantimilan  C - Arrangement     GNU C++     Accepted    1000 ms     9600 KB
//666303  Sep 3, 2011 11:17:49 PM     lantimilan  C - Arrangement     GNU C++     Wrong answer on test 7  50 ms   9600 KB
//666284  Sep 3, 2011 11:11:19 PM     lantimilan  C - Arrangement     GNU C++     Wrong answer on test 3  80 ms   9600 KB
//665890  Sep 3, 2011 9:09:52 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 7  80 ms   9600 KB
//665888  Sep 3, 2011 9:09:14 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 1  10 ms   9600 KB
//665843  Sep 3, 2011 9:01:35 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 3  80 ms   9600 KB
//665837  Sep 3, 2011 9:00:38 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 1  30 ms   9600 KB
//665832  Sep 3, 2011 8:59:50 PM  lantimilan  C - Arrangement     GNU C++     Compilation error   0 ms    0 KB

