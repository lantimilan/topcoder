// =========================================================
// 
//       Filename:  prob67D.cpp
// 
//    Description:  D. Big Maximum Sum
// 
//        Version:  1.0
//        Created:  04/13/2011 09:31:48 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/13/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <vector>
using namespace std;

template<class T>
void checkmax(T &a, T b)
{ if (a<b) a=b; }

void print(const vector<int> &v)
{
    for(int i=0; i<int(v.size()); ++i) cout << v[i] << " ";
    cout << endl;
}

void solve()
{
    int n,m; cin >> n >> m;
    vector<int> pre, post, mid, all;
    for(int i=0; i<n; ++i)
    {
        int len; cin >> len;
        vector<int> v(len);
        for(int k=0; k<len; ++k) cin >> v[k];

        int bestpre=v[0], bestpost=v[len-1], bestmid=-2000, bestall=0;
        for(int k=0; k<len; ++k) { checkmax(bestmid,v[k]); bestall+=v[k]; }
        for(int k=0, curr=0; k<len; ++k)
        { curr += v[k]; checkmax(bestpre, curr); }
        for(int k=len-1, curr=0; k>=0; --k)
        { curr += v[k]; checkmax(bestpost, curr); }
        for(int k=0,curr=0; k<len; ++k)
        { curr += v[k]; if (curr>=0) { checkmax(bestmid, curr); } else curr=0; }

        pre.push_back(bestpre);
        post.push_back(bestpost);
        mid.push_back(bestmid);
        all.push_back(bestall);
    }

    //print(pre); print(post); print(mid); print(all);

    vector<int> hit(n);
    vector<int> ids(m);
    for(int i=0; i<m; ++i)
    {
        int k; cin >> k; --k; 
        hit[k]++; ids[i] = k;
    }
    long long best = -2000;
    for(int i=0; i<n; ++i) if (hit[i]) checkmax(best, (long long)mid[i]);

    int x=0; long long curr=0LL;
    while(x<m) {
        int pos=ids[x]; //cout << pos+1 << " " << best << " " << curr << endl;
        checkmax(best,curr+pre[ids[x]]);
        if (curr+all[pos] >= post[pos]) curr += all[pos];
        else curr = post[pos];
        ++x;
    }

    cout << best << endl;
}
int main()
{
    solve();
}

/* *************************
 * #    When    Who     Problem     Lang    Verdict     Time    Memory
 * 386961   Apr 13, 2011 11:19:30 PM    lantimilan  D - Big Maximum Sum     GNU
 * C++  Accepted    890 ms  2400 KB
 * 386929   Apr 13, 2011 11:06:43 PM    lantimilan  D - Big Maximum Sum     GNU
 * C++  Wrong answer on test 27     830 ms  2400 KB
 * 386855   Apr 13, 2011 10:46:52 PM    lantimilan  D - Big Maximum Sum     GNU
 * C++  Wrong answer on test 4  10 ms   1400 KB
 * 386829   Apr 13, 2011 10:41:54 PM    lantimilan  D - Big Maximum Sum     GNU
 * C++  Wrong answer on test 4  10 ms   1400 KB
 * 386726   Apr 13, 2011 10:18:05 PM    lantimilan  D - Big Maximum Sum     GNU
 * C++  Wrong answer on test 3  10 ms   1400 KB
 * 386378   Apr 13, 2011 9:35:08 PM     lantimilan  A - Life Without Zeros  GNU
 * C++  Accepted    30 ms   1400 KB
 * 386371   Apr 13, 2011 9:34:41 PM     lantimilan  D - Big Maximum Sum     GNU
 * C++  Wrong answer on test 3  10 ms   1400 KB 
 * */
