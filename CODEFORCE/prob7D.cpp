// =========================================================
// 
//       Filename:  prob7D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/02/2011 05:03:22 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/02/2011, LI YAN
// 
// =========================================================

// check all prefix palindrome or not
//
// one observation is that if s is palindrome and left half is palindrome, then
// right half is also palindrome and left and right have the same pal degree.
//
// Algorithm 1:
// let s2 = s$s^R
// then every period of s2 corresponds to a prefix palindrome
// now use KMP to get all periods
//
// Algorithm 2:
// Manacher's algorithm, computes all maximal infix palindrome in O(n) time
//
// Let R[i] be the radius of palindrome center at s[i]|s[i+1]
// suppose we know R[i], then we can extend to R[i+k] as long as i+k <= R[i]
// and R[i-k]!=R[i]-k, that is, R[i-k] has not exceeded the left boundary of
// R[i]
// R[i+k] = min(R[i-k],R[i]-k)
//
// The reason is: if R[i-k] < R[i]-k, then we can reflect w.r.t. center i
// else R[i-k] > R[i]-k, now R[i+k]>=R[i]-k because a subpalindrome center i-k
// with radius R[i]-k exists. However R[i+k] cannot be bigger than R[i]-k.
// Otherwise s[i+k + R[i]-k+1] will get mapped into R[i] and reflect to some
// char within R[i-k], which is beyond R[i]-k. However this contradicts with the
// maximality of R[i].
//
// If we have R[i-k]=R[i]-k, then we could have R[i+k] grow. So we compare char
// by char from right boundary R[i]+k and find out R[i+k].
//
// As each char is compared once, it is O(n).

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long LL;

void solve()
{
    string s; cin >> s;

    int n = s.size();

    string s2=s; reverse(s2.begin(), s2.end());
    s2 = s + '$' + s2; //cout << s2 << endl;
    int n2 = s2.size();
    // q[i] is length of longest prefix that matches the suffix end at s[i]
    vector<int> q(n2,0); 
    // KMP
    for(int i=1; i<n2; ++i)
    {
        int p=i-1;
        while(q[p] && s2[i]!=s2[q[p]]) { p=q[p]-1; }
        if (s2[i]==s2[q[p]]) q[i]=q[p]+1;
    }

    //for(int i=0; i<n2; ++i) cout << q[i] << ' '; cout << endl;

    vector<int> prefix(n,0);
    int p=n2-1;
    while(q[p]>0) { prefix[q[p]-1]=1; p=q[p]-1; } //cout << p << endl; }

    vector<int> dp(n,0); dp[0]=1;
    for(int i=1; i<n; ++i)
    { if (prefix[i]) dp[i]=dp[(i-1)/2]+1; }

    LL ans=0;
    for(int i=0; i<n; ++i) ans+=dp[i];

    cout << ans << endl;
}

int main()
{
    solve();
}

// 577065   Aug 3, 2011 8:33:30 AM  lantimilan  D - Palindrome Degree   GNU C++
// Accepted     830 ms  97700 KB
// 577063   Aug 3, 2011 8:26:42 AM  lantimilan  D - Palindrome Degree   GNU C++
// Wrong answer on test 3   10 ms   1400 KB
