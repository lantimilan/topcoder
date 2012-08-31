// =========================================================
// 
//       Filename:  prob119C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/14/2011 08:27:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/14/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
map<pair<LL,pii>,pair<LL,pair<int,LL> > > dp; // (hw,(day,last)) = (total,(prev,prevhw))

struct subject_t {
    LL a,b;
    int c;
    int index;
};

bool operator<(const subject_t &s1, const subject_t &s2)
{
    return s1.c < s2.c;
}

int main()
{
    int n,m,k; cin >> n >> m >> k;

    vector<subject_t> subs(m);
    for(int i=0; i<m; ++i) {
        cin >> subs[i].a >> subs[i].b >> subs[i].c;
        subs[i].index=i;
    }
    sort(subs.begin(), subs.end());

    for(int last=0; last<m; ++last)
    for(LL hw=subs[last].a; hw<=subs[last].b; ++hw)
    {
        pair<LL,pii> key=make_pair(hw,pii(0,last));
        dp[key]=make_pair(hw,make_pair(-1,-1LL));
    }
    for(int day=0; day<n-1; ++day)
    for(int last=0; last<m; ++last)
    for(LL hw=subs[last].a; hw<=subs[last].b; ++hw)
    {
        pair<LL,pii> key=make_pair(hw,pii(day,last));

            if (!dp.count(key)) continue;
            for(int next=last+1; next<m; next++) if (subs[next].c > subs[last].c)
            {
                LL lo=subs[next].a;
                LL hi=subs[next].b;
                LL nexthw=hw+k;
                if (lo<=nexthw && nexthw<=hi)
                {
                    if (nexthw==hw+k || nexthw==hw*k) {
                        pair<LL,pii> nextkey=make_pair(nexthw,pii(day+1,next));
                        LL newval = dp[key].first + nexthw;
                        if (newval > dp[nextkey].first) {
                            dp[nextkey]=make_pair(newval,make_pair(last,hw));
                            //cout << day << ' ' << last << ' ' << hw << ' '
                            //    << day+1 << ' ' << next << ' ' << nexthw << ' '
                            //    << newval << endl;
                        }
                    }
                }

                nexthw=hw*k;
                if (lo<=nexthw && nexthw<=hi)
                {
                    if (nexthw==hw+k || nexthw==hw*k) {
                        pair<LL,pii> nextkey=make_pair(nexthw,pii(day+1,next));
                        LL newval = dp[key].first + nexthw;
                        if (newval > dp[nextkey].first) {
                            dp[nextkey]=make_pair(newval,make_pair(last,hw));
                            //cout << day << ' ' << last << ' ' << hw << ' '
                            //    << day+1 << ' ' << next << ' ' << nexthw << ' '
                            //    << newval << endl;
                        }
                    }
                }
            }
    }
    LL best=0;
    pair<LL,pii> key,bestkey;
    for(int last=0; last<m; ++last)
    for(LL hw=subs[last].a; hw<=subs[last].b; ++hw)
    {
        key=make_pair(hw,pii(n-1,last));
        LL val = dp[key].first;
        if (val>best) {
            best=val; bestkey=key;
        }
    }
    if (best==0) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        vector<pair<int,LL> > ans; 
        key=bestkey;

        for(int i=0; i<n; ++i) {
            LL hw=key.first; int id=subs[key.second.second].index+1;
            ans.push_back(make_pair(id,hw));
            int day=n-2-i; // off-by-one, day is prev
            int last=dp[key].second.first;
            LL prevhw=dp[key].second.second;
            key=make_pair(prevhw,make_pair(day,last));
        }
        /* this also works
        LL hw=key.first; int id=subs[key.second.second].index+1;
        ans.push_back(make_pair(id,hw));
        for(int i=1; i<n; ++i) {
            int day=n-1-i;
            int last=dp[key].second.first;
            LL prevhw=dp[key].second.second;
            key=make_pair(prevhw,make_pair(day,last));
            LL hw=key.first; int id=subs[key.second.second].index+1;
            ans.push_back(make_pair(id,hw));
        }
        */
        reverse(ans.begin(), ans.end());
        for(int i=0; i<n; ++i) {
            cout << ans[i].first << ' ' << ans[i].second << endl;
        }
    }
}

// 765823   Oct 14, 2011 9:37:40 PM     lantimilan  C - Education Reform    GNU C++     Accepted    1080 ms     9760 KB
// one TLE since we do not have to iterate all nexthw, know this but thought the constraints are small enough, they ARE NOT
// 765714  Oct 14, 2011 9:34:26 PM     lantimilan  C - Education Reform    GNU C++     Time limit exceeded on test 16  2000 ms     6088 KB
// 
// two WA due to day off-by-one when reconstruct ans[]
//
// 764521   Oct 14, 2011 8:33:42 PM     lantimilan  C - Education Reform    GNU C++     Wrong answer on pretest 3   10 ms   1444 KB
// 763979  Oct 14, 2011 8:20:14 PM     lantimilan  C - Education Reform    GNU C++     Wrong answer on pretest 3   30 ms   1444 KB 
