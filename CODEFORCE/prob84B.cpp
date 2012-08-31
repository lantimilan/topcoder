// =========================================================
// 
//       Filename:  B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/13/2011 09:00:01 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/13/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
void solve()
{
    int n; cin >> n;
    vector<int> vec(n);
    for(int i=0; i<n; ++i) cin >> vec[i];

    LL ans=0;
    int begin=0;
    for(; begin<n; )
    {
        int end;
        for(end=begin; end<n && vec[end]==vec[begin]; ++end);
        end--;
        ans += (end-begin+2)*LL(end-begin+1)/2;
        begin=end+1;
    }
    cout << ans << endl;
}
int main()
{
    solve();
}
