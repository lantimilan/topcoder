// =========================================================
// 
//       Filename:  CAKEDOOM.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/01/2012 11:36:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/01/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

// K=1, len=1
// K>=3, can always use min color since each pos has only two neighbors
// K=2, try 0, then try 1, then fail
// return empty string if no solution
string getmin(const string &query, int K)
{
    int n=query.size();
    // special case len=1
    if (n==1) {
        if (query[0]=='?') return "0";
        else return query;
    }
    string ans=query;
    bool good;
    for(int i=0; i<n; ++i) if (query[i]!='?' && query[i]>='0'+K) return "";
    if (K==1) {
        return "";
    }
    else if (K==2) {
        // try 0
        ans=query; good=true;
        for(int i=0; i<n; ++i) if (ans[i]=='?') { ans[i]='0'; break; }
        for(int i=0; i<n; ++i) {
            int left, right;
            left=(i-1+n)%n; right=(i+1)%n;
            if (ans[i]!='?' && (ans[i]==ans[left] || ans[i]==ans[right])) {
                good=false; break;
            }
            if (ans[i]=='?') {
                if (ans[left]==ans[right] || ans[right]=='?') {
                    assert(ans[left]!='?');
                    ans[i]='0'+(1-(ans[left]-'0'));
                }
                else {
                    good=false; break;
                }
            }
        }
        if (good) return ans;
        // try 1
        ans=query; good=true;
        for(int i=0; i<n; ++i) if (ans[i]=='?') { ans[i]='1'; break; }
        for(int i=0; i<n; ++i) {
            int left, right;
            left=(i-1+n)%n; right=(i+1)%n;
            if (ans[i]!='?' && (ans[i]==ans[left] || ans[i]==ans[right])) {
                good=false; break;
            }
            if (ans[i]=='?') {
                if (ans[left]==ans[right] || ans[right]=='?') {
                    assert(ans[left]!='?');
                    ans[i]='0'+(1-(ans[left]-'0'));
                }
                else {
                    good=false; break;
                }
            }
        }
        if (good) return ans;
        else return "";
    }
    else { // K>=3, use min color
        for(int i=0; i<n; ++i) {
            int left, right;
            char ch;
            left=(i-1+n)%n; right=(i+1)%n;
            if (ans[i]!='?') {
                if (ans[i]==ans[left] || ans[i]==ans[right]) return "";
            }
            else { // ans[i]=='?'
                for(ch='0'; ch<'0'+K; ++ch) {
                    if (ch != ans[left] && ch != ans[right]) break;
                }
                ans[i]=ch;
            }
        }
        return ans;
    }
}

int main()
{
    int T; cin >> T;
    while(T--) {
        int K; cin >> K; cin.ignore(1024, '\n');
        string query;
        getline(cin, query);
        string ans = getmin(query, K);
        if (ans.empty()) cout << "NO" << endl;
        else cout << ans << endl;
    }

}
