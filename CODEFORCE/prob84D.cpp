// =========================================================
// 
//       Filename:  D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/13/2011 10:33:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/13/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

void solve()
{
    LL n, k; cin >> n >> k;
    VI animal(n);
    LL sum=0;
    for(int i=0; i<n; ++i) { cin >> animal[i]; sum += animal[i]; }

    if (sum < k) { cout << -1 << endl; return; }

    LL lo=0, hi=k;
    while(lo<=hi)
    {
        LL mid=(lo+hi)/2;
        LL curr=0;
        for(int i=0; i<n; ++i) curr += min(LL(animal[i]), mid);
        if (curr==k) { lo=hi=mid; break; }
        else if (curr<k) { lo=mid+1; }
        else { hi=mid-1; }
    }
    LL target=hi, total=0;
    for(int i=0; i<n; ++i) total += min(LL(animal[i]), target);
    assert(total <= k);
    VI ans;
    for(int i=0; i<n; ++i) animal[i] = max(0LL, animal[i]-target);

    //for(int i=0; i<n; ++i) cout << animal[i] << " "; cout << endl;

    int last=-1, rem=k-total; 
    for(int i=0; i<n && rem; ++i) if (animal[i]) { animal[i]--; rem--; last=i; }
    for(int i=last+1; i<n; ++i) if (animal[i]) ans.PB(i+1);
    for(int i=0; i<=last; ++i) if (animal[i]) ans.PB(i+1);
    bool first=true;
    for(int i=0; i<int(ans.size()); ++i)
    { if (!first) cout << " "; cout << ans[i]; first=false; }
    cout << endl;
}

int main()
{
    solve();
}

/* **********************
 *453935     May 14, 2011 2:35:29 AM    lantimilan        D - Doctor     GNU C++     Accepted        220 ms      2600 KB
 453932     May 14, 2011 2:33:29 AM     lantimilan  D - Doctor  GNU C++     Wrong answer on test 6  30 ms   1400 KB 
 * */
