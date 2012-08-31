// =========================================================
// 
//       Filename:  prob115B.cpp
// 
//    Description:  http://codeforces.com/contest/115/problem/B
// 
//        Version:  1.0
//        Created:  09/15/2011 08:21:00 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n,m; cin >> n >> m;

    vector<string> garden(n);
    vector<int> left(n), right(n);
    for(int i=0; i<n; ++i) cin >> garden[i];

    for(int i=0; i<n; ++i)
    {
        left[i]=right[i]=-1;
        for(int j=0; j<m; ++j) if (garden[i][j]=='W')
        {
            right[i]=j;
            if (left[i]<0) left[i]=j;
        }
        //cout << left[i] << ' ' << right[i] << endl;
    }

    int pos=0, ans=0;
    for(int i=0; i<n; )
    {
        int next;
        if (i%2==0) { next=right[i]; }
        else { next=left[i]; }
        if (next>=0) ans+=abs(next-pos); // cover current row
        // cover next nonempty row
        int k;
        for(k=i+1; k<n; ++k) if (left[k]>=0) break;
        if (k<n)
        {
                ans+=k-i;
                if (k%2==0) { // i move to left[k]
                    if (next<0) next=pos;
                    ans+=abs(next-left[k]);
                    next=left[k];
                }
                else { // i move to right[k]
                    if (next<0) next=pos;
                    ans+=abs(next-right[k]);
                    next=right[k];
                }
        }
        if (next>=0) pos=next;
        i=k;
        //cout << ans << endl;
    }
    cout << ans << endl;
}

// 703016   Sep 15, 2011 11:33:48 PM    lantimilan  B - Lawnmower   GNU C++
// Accepted     30 ms   1400 KB
// 702998   Sep 15, 2011 11:26:13 PM    lantimilan  B - Lawnmower   GNU C++
// Wrong answer on test 8   30 ms   1400 KB
// 702974   Sep 15, 2011 11:20:59 PM    lantimilan  B - Lawnmower   GNU C++
// Wrong answer on test 8   10 ms   1400 KB
// 702514   Sep 15, 2011 10:20:07 PM    lantimilan  B - Lawnmower   GNU C++
// Time limit exceeded on test 7    3000 ms     32900 KB
// 702501   Sep 15, 2011 10:19:32 PM    lantimilan  B - Lawnmower   GNU C++
// Wrong answer on test 3   50 ms   32700 KB
// 702383   Sep 15, 2011 10:15:08 PM    lantimilan  B - Lawnmower   GNU C++
// Time limit exceeded on test 7    3000 ms     32900 KB 
//
// 699135   Sep 15, 2011 7:43:31 PM     lantimilan  B - Lawnmower   GNU C++
// Wrong answer on pretest 8    10 ms   1400 KB
// 698463   Sep 15, 2011 7:32:28 PM     lantimilan  B - Lawnmower   GNU C++
// Wrong answer on pretest 8    10 ms   1400 KB 
