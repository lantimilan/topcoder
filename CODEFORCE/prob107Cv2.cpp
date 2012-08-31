// http://codeforces.com/contest/107/problem/C
//
#include <iostream>
using namespace std;

int bitcnt(int k)
{
    int ans=0;
    while(k) { k&=k-1; ++ans; }
    return ans;
}

int main()
{
    int pred[20]={0};
    int n,m; long long y; cin >> n >> y >> m;
    for(int i=0; i<m; ++i)
    {
        int a,b; cin >> a >> b; --a; --b;
        pred[b] |= 1<<a;
    }

    y-=2000;
    int seat[20], prof[20]; // seat[pos]=elem, prof[elem]=pos
    long long cnt=0LL;
    for(int i=0; i<n; ++i) seat[i]=prof[i]=-1;
    for(int pos=0; pos<n; ++pos)
    {
    for(int elem=0; elem<n; ++elem) if (prof[elem]==-1)
    {
        prof[elem]=pos;
        // count #perms consistent with previous 0..pos assignment
        // and the pred[] constraint
        long long dp[1<<20]={0LL};
        dp[0]=1;
        for(int s=1; s<(1<<n); ++s)
        {
            int k=bitcnt(s)-1; // s has elem[0..k] with pos bit set in s
            if (prof[k]!=-1) { // prof[k] already fixed at some pos
                int p=prof[k];
                if ((s&1<<p) && (s&pred[p])==pred[p])
                    dp[s]+=dp[s^1<<p];
            }
            else {
                for(int p=0; p<n; ++p) 
                    if ((s&1<<p) && (s&pred[p])==pred[p])
                        dp[s]+=dp[s^1<<p];
            }
        }
        //for(int i=0; i<(1<<n); ++i) cout << dp[i] << ' '; cout << endl;
        cnt = dp[(1<<n)-1];
        //cout << pos << ' ' << elem << ' ' << cnt << endl;
        if (cnt >= y) { seat[pos]=elem; break; }
        else { y-=cnt; prof[elem]=-1;}
    }
    if (seat[pos]==-1) { cout << "The times have changed" << endl; return 0; }
    }
    //cout << y << endl;
    y-=cnt;
    if (y>0) cout << "The times have changed" << endl;
    else {
        for(int p=0; p<n; ++p)
        {
            if (p) cout << ' ';
            cout << seat[p]+1;
        }
        cout << endl;
    }
}

//666817    Sep 4, 2011 7:54:11 AM  lantimilan  C - Arrangement     GNU C++     Accepted    1050 ms     9600 KB
//666593  Sep 4, 2011 3:25:35 AM  lantimilan  C - Arrangement     GNU C++     Accepted    1000 ms     9600 KB
//666303  Sep 3, 2011 11:17:49 PM     lantimilan  C - Arrangement     GNU C++     Wrong answer on test 7  50 ms   9600 KB
//666284  Sep 3, 2011 11:11:19 PM     lantimilan  C - Arrangement     GNU C++     Wrong answer on test 3  80 ms   9600 KB
//665890  Sep 3, 2011 9:09:52 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 7  80 ms   9600 KB
//665888  Sep 3, 2011 9:09:14 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 1  10 ms   9600 KB
//665843  Sep 3, 2011 9:01:35 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 3  80 ms   9600 KB
//665837  Sep 3, 2011 9:00:38 PM  lantimilan  C - Arrangement     GNU C++     Wrong answer on test 1  30 ms   9600 KB
//665832  Sep 3, 2011 8:59:50 PM  lantimilan  C - Arrangement     GNU C++     Compilation error   0 ms    0 KB 
//
