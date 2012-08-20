// =========================================================
// 
//       Filename:  FAVNUM.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/06/2012 10:30:32 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/06/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;
int64 L, R, K, N;
vector<int> fav;
int len[65];
int digits[65][20];

class MyCmp {
public:
    bool operator()(const string &s1, const string &s2) {
        if (s1.length() != s2.length())
            return s1.length() < s2.length();
        else
            return s1 < s2;
    }
};

int64 calc(int64 cap)
{
    int lim[20];
    int l=0;
    for(int i=0; i<18 && cap; ++i, ++l) {
        lim[i] = cap%10;
        cap/=10;
    }
    for(int i=0, j=l-1; i<j; ++i, --j) {
        int t=lim[i]; lim[i]=lim[j]; lim[j]=t;
    }
    int cnt[20], all[65][20][20], sub[65][20][20];
    int all2[65][20][20], sub2[65][20][20];
    memset(cnt, 0, sizeof cnt);
    memset(all, 0, sizeof all);
    memset(sub, 0, sizeof sub);

    for(int i=0; i<18; ++i) { // pos
        cnt[i+1]+=cnt[i];
        for(int d=0; d<10; ++d) // digit
        for(int x=0; x<int(fav.size()); ++x)
        for(int j=0; j<18; ++j) {
            if (d==digits[x][j]) {
                if (j<len[x]) all2[x][i+1][j+1] += all[x][i][j];
                else if (j==len[x]) cnt[i+1] += all[x][i][j];
            }
        }
    }
}

int main()
{
    pow10[0]=1;
    for(int i=1; i<=18; ++i) {
        pow10[i]=10*pow10[i-1];
    }
    cin >> L >> R >> K >> N;
    vector<string> tmp(N);
    for(int i=0; i<N; ++i) {
        cin >> tmp[i];
    }
    // remove all int that is a superstring of another int
    sort(tmp.begin(), tmp.end(), MyCmp());
    for(int i=0; i<N; ++i) {
        bool good=true;
        for(int j=0; j<i; ++j)
            if (tmp[i].find(tmp[j]) != string::npos)
                good=false;
        if (good) {
            fav.push_back(atoi(tmp[i].c_str()));
        }
    }
    for(int i=0; i<int(fav.size()); ++i)
        cout << fav[i] << ' ';
    cout << endl;

    for(int i=0; i<int(fav.size()); ++i) {
        int64 t = fav[i];
        while(t) {
            digits[i][len[i]++]=t%10;
            t/=10;
        }
        for(int a=0, b=len[i]-1; a<b; ++a, --b) {
            int t = digits[i][a]; 
            digits[i][a]=digits[i][b];
            digits[i][b]=t;
        }
    }
        

    int64 ans;
    ans = calc(R);
    ans -= calc(L-1);
    cout << ans << endl;
}
