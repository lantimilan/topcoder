// =========================================================
// 
//       Filename:  recipe.cpp
// 
//    Description:  Remember the recipe
//
//    Problem code: TWSTR
// 
//        Version:  1.0
//        Created:  05/03/2012 08:12:37 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

typedef pair<string, int> psi;

psi vec[1005];

int mycmp(const string &key, const string &other)
{
    int n=key.length();
    for(int i=0; i<n; ++i) {
        if (i>=other.length()) return 1;
        if (key[i] > other[i]) return 1;
        if (key[i] < other[i]) return -1;
    }
    return 0;
}

// implements lower_bound of stl
int lower(int N, const string &key)
{
    int lo=-1, hi=N; // invariant: vec[lo]<key, vec[hi]>=key
    while(lo+1 < hi) { // loop must be entered at least once if N>=1
        int m = (lo+hi)/2; // lo < m < hi and m is a valid index
        int res = mycmp(key, vec[m].first);
        if (res<=0) hi=m;
        else lo=m;
    }
    if (hi<N && mycmp(key, vec[hi].first)==0) return hi;
    else return -1;
}

int upper(int N, const string &key)
{
    int lo=-1, hi=N; // invariant: vec[lo]<=key, vec[hi]>key
    while(lo+1 < hi) { // loop must be entered at least once if N>=1
        int m = (lo+hi)/2; // lo < m < hi and m is a valid index
        int res = mycmp(key, vec[m].first);
        if (res<0) hi=m;
        else lo=m;
    }
    if (0<=lo && mycmp(key, vec[lo].first)==0) return lo;
    else return -1;
}

int main()
{
    int N; cin >> N;
    for(int i=0; i<N; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    sort(vec, vec+N);

    int Q; cin >> Q;
    for(int i=0; i<Q; ++i) {
        string key; cin >> key;
        int low = lower(N, key);
        int upp = upper(N, key);
        if (low<0) cout << "NO" << endl;
        else {
            int val=vec[low].second;
            string ans=vec[low].first;
            for(int k=low+1; k<=upp; k++) {
                if (vec[k].second > val) {
                    val = vec[k].second;
                    ans = vec[k].first;
                }
            }
            cout << ans << endl;
        }
    }
}
