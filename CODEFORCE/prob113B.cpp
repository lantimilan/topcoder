// =========================================================
// 
//       Filename:  prob113B.cpp
// 
//    Description:  http://codeforces.ru/contest/113/problem/B
// 
//        Version:  1.0
//        Created:  09/08/2011 08:54:31 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/08/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
using namespace std;

string text, sbegin, send;
bool beginmap[2010],endmap[2010];

bool cmp(int a, int b)
{
/*  
    int n=int(text.size());
    for(int x=a,y=b; x<n&&y<n; ++x,++y)
    {
        if (text[x]<text[y]) return true;
        if (text[x]>text[y]) return false;
    }
    if (a>b) return true;
    return false;
    */
    return text.substr(a) < text.substr(b);
}

void match(const string &text, const string &sub, bool mp[])
{
    vector<int> ans;
    int n=int(text.size()), m=int(sub.size());
    for(int i=0; i<n; ++i)
    {
        int k;
        for(k=0; k<m; ++k)
        {
            if (i+k>=n || sub[k]!=text[i+k]) break;
        }
        if (k>=m) mp[i]=true;
    }
}

int main()
{
    cin >> text >> sbegin >> send;

    match(text,sbegin,beginmap);
    match(text,send,endmap);

    int n=int(text.size());
    vector<int> suffix;
    for(int i=0; i<n; ++i) suffix.push_back(i);
    sort(suffix.begin(), suffix.end(), cmp);

    //for(int i=0; i<n; ++i) cout << text.substr(suffix[i]) << endl;

    int ans=0;
    int k1=int(sbegin.size()), k2=int(send.size());
    int lcp[2010]={0};
    for(int i=1; i<n; ++i)
    {
        int k;
        int a=suffix[i-1],b=suffix[i];
        for(k=0; a+k<n && b+k<n; ++k)
        { 
            if (text[a+k]!=text[b+k]) break; 
        }
        lcp[i]=k;
    }
    //for(int i=0; i<n; ++i) cout << lcp[i] << ' '; cout << endl;

    for(int i=0; i<n; ++i)
    {
        int l=max(k1,k2); l=max(l,lcp[i]+1);
        for(; l<=n-suffix[i]; ++l)
        {
            int begin=suffix[i], end=suffix[i]+l;
            if (beginmap[begin] && endmap[end-k2]) ++ans;
        }
    }

    cout << ans << endl;
}

// 684197   Sep 9, 2011 4:54:27 AM  lantimilan  B - Petr#   GNU C++     Accepted
// 230 ms   1500 KB 
//
// you need the idea of lcp[]
//
// Seems gcc 4.6 is very inefficient in string copying
// No, it is not. MSVC is simply too good at strcmp
//
// 684121   Sep 9, 2011 4:13:47 AM  lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 19    2000 ms     1500 KB
// 684118   Sep 9, 2011 4:13:03 AM  lantimilan  B - Petr#   MS C++  Accepted
// 1060 ms  1500 KB
// 684099   Sep 9, 2011 4:01:31 AM  lantimilan  B - Petr#   MS C++  Accepted
// 1230 ms  1500 KB
// 684089   Sep 9, 2011 3:57:28 AM  lantimilan  B - Petr#   MS C++  Time limit
// exceeded on test 19  2000 ms     1400 KB
// 684086   Sep 9, 2011 3:57:06 AM  lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 19    2000 ms     1400 KB
// 684001   Sep 9, 2011 3:16:31 AM  lantimilan  B - Petr#   MS C++  Accepted
// 1250 ms  1500 KB
// 683985   Sep 9, 2011 3:06:01 AM  lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 19    2000 ms     1500 KB
// 683979   Sep 9, 2011 3:02:34 AM  lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 19    2000 ms     1500 KB
// 683968   Sep 9, 2011 2:54:07 AM  lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 19    2000 ms     11100 KB
// 683669   Sep 9, 2011 12:47:17 AM     lantimilan  B - Petr#   GNU C++     Time
// limit exceeded on test 21    2000 ms     1400 KB
// 683338   Sep 8, 2011 11:53:22 PM     lantimilan  B - Petr#   GNU C++
// Wrong answer on test 41  860 ms  3300 KB
// 683271   Sep 8, 2011 11:46:09 PM     lantimilan  B - Petr#   GNU C++
// Wrong answer on test 24  880 ms  1900 KB 
//
