// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/08/2011 08:14:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/08/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
using namespace std;

#define sz(a) int(a.size())

int main()
{
    string words[3][2]; // [adj,noun,verb][mascu,femi]
    words[0][0]="lios"; words[0][1]="liala";
    words[1][0]="etr";  words[1][1]="etra";
    words[2][0]="initis";words[2][1]="inites";

    int gender=-1;
    int total=0;
    int cnt[3]={0};
    string text;
    while(cin >> text)
    {
        int tt,gg; tt=gg=-1;
        for(int i=0; i<3; ++i) for(int j=0; j<2; ++j)
        {
            if (sz(text)<sz(words[i][j])) continue;
            int p,q;
            for(p=sz(words[i][j])-1,q=sz(text)-1; p>=0; --p,--q)
            {
                if (words[i][j][p]!=text[q]) break;
            }
            if (p<0) { tt=i; gg=j; goto done;}
        }
        done:
        if (tt>=0 && gg>=0) {
            total++;
            if (gender<0) { gender=gg; }
            else { if (gender!=gg) { gender=100; break; } }
            if (tt==0) { if (cnt[1]>=1) { cnt[0]=-1; break; } }
            else if (tt==1) { if (cnt[1]>=1) { cnt[0]=-1; break; }}
            else { if (cnt[1]==0) { cnt[0]=-1; break; }}
            cnt[tt]++;
        }
    }
    //cout << cnt[0] << ' ' << cnt[1] << ' ' << cnt[2] << endl;
    //cout << gender << endl;
    if (total==1) cout << "YES" << endl;
    else if (cnt[0]>=0)
    {
        if (gender < 100 && cnt[1]==1) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    else cout << "NO" << endl;
}
