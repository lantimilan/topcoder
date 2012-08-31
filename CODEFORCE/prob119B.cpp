// =========================================================
// 
//       Filename:  prob119B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/14/2011 09:53:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/14/2011, LI YAN
// 
// =========================================================
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define sz(a) int((a).size())

int main()
{
    int n,k; cin >> n >> k;
    int kk=n/k;
    vector<int> thm(n);
    vector<int> mark(n);
    for(int i=0; i<n; ++i) cin >> thm[i];
    int q; cin >> q;
    double xmin=-1.0, xmax=-1.0;
    for(int i=0; i<q; ++i)
    {
        double sum=0.0;
        for(int j=0; j<kk; ++j)
        {
            int x; cin >> x; sum+=thm[x-1];
            mark[x-1]=1;
        }
        sum/=kk; //cout << sum << endl;
        if (xmin<0 || xmin>sum) xmin=sum;
        if (xmax<0 || xmax<sum) xmax=sum;
    }
    vector<int> remain;
    for(int i=0; i<n; ++i) if (!mark[i]) remain.push_back(thm[i]);
    sort(remain.begin(), remain.end());
    if (sz(remain)>=kk && sz(remain)>n-k*kk) {
        double sum=0.0;
        for(int i=0; i<kk; ++i) {
            sum+=remain[i];    
        }
        sum/=kk; //cout << sum << endl;
        if (xmin<0 || xmin>sum) xmin=sum;
        if (xmax<0 || xmax<sum) xmax=sum;

        sum=0.0;
        for(int i=0; i<kk; ++i) {
            sum+=remain[sz(remain)-1-i];    
        }
        sum/=kk; //cout << sum << endl;
        if (xmin<0 || xmin>sum) xmin=sum;
        if (xmax<0 || xmax<sum) xmax=sum;
    }
    cout << fixed << setprecision(10)
        << xmin << ' ' << xmax << endl;
}
