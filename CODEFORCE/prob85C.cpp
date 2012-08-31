// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  Yandex 2011 Round 1
// 
//        Version:  1.0
//        Created:  05/20/2011 09:19:07 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/20/2011, LI YAN
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
typedef pair<LL,LL> PLL;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

struct node_t {
    LL minval, maxval, key;
    LL id, paid, left, right;
};

ostream& operator<<(ostream &os, const node_t &d)
{ return os << " " <<  d.key << " " <<  d.id << " " <<  d.paid 
    << " " <<  d.left << " " <<  d.right << " " <<  d.minval << " " <<  d.maxval; }

void checkmin(LL &a, LL b) { if (a>b) a=b; }
void checkmax(LL &a, LL b) { if (a<b) a=b; }

void calc(vector<PLL> &keypairs, int begin, int end,
    const vector<node_t> &nodes, int root, vector<LL> &sum, vector<LL> &cnt, LL cum, LL tot)
{
//    cout << "calc: " << begin << " " << end << " " << nodes[root].key << endl;
//    int k=sum.size();
//    for(int i=0; i<k; ++i) cout << sum[i] << " "; cout << endl;
//    for(int i=0; i<k; ++i) cout << cnt[i] << " "; cout << endl;

    if (begin >= end || nodes[root].left<0) return;
    vector<PLL>::iterator it = lower_bound(keypairs.begin(), keypairs.end(), make_pair(nodes[root].key,0LL));
    assert(it==keypairs.end() || it->first > nodes[root].key);
    // choose left, then all right mistake once
        int index = it - keypairs.begin();
        int subleft = nodes[root].left, subright = nodes[root].right;
        //for(int i=max(begin,index); i<end; ++i) { sum[i]+=nodes[subleft].maxval; cnt[i]++; }
        calc(keypairs, begin, index, nodes, subleft, sum, cnt, cum+nodes[subleft].maxval, tot+1);
    // choose right, then all left done
        //for(int i=begin; i<min(index,end); ++i)  { sum[i]+=nodes[subright].minval; cnt[i]++; }
        calc(keypairs, index, end, nodes, subright, sum, cnt, cum+nodes[subright].minval, tot+1);
}

PLL setminmax(vector<node_t> &nodes, int root)
{
    if (nodes[root].left<0) return PLL(nodes[root].key,nodes[root].key);
    nodes[root].minval = setminmax(nodes, nodes[root].left).first;
    nodes[root].maxval = setminmax(nodes, nodes[root].right).second;
    return PLL(nodes[root].minval, nodes[root].maxval);
}

void solve()
{
    int n; cin >> n;
    vector<node_t> nodes(n);
    int root=-1;
    for(int i=0; i<n; ++i) { 
        int paid, key;
        cin >> paid >> key;
        if (paid < 0) root = i; 
        paid--;
        nodes[i].id = i; nodes[i].paid = paid; nodes[i].key = key; 
        nodes[i].minval = nodes[i].maxval = key;
        nodes[i].left = nodes[i].right = -1;
    }
    for(int i=0; i<n; ++i) if (nodes[i].paid>=0) {
        int pa = nodes[i].paid; int k = nodes[i].key;
        if (k<nodes[pa].key) nodes[pa].left = i;
        else nodes[pa].right = i;
    }
    assert(root>=0);
    setminmax(nodes, root);

    //for(int i=0; i<n; ++i) cout << nodes[i] << endl;

    int k; cin >> k;
    vector<PLL> keypairs(k);
    for(int i=0; i<k; ++i) { 
        int x; cin >> x; 
        keypairs[i].first = x; keypairs[i].second = i;
    }
    sort(keypairs.begin(), keypairs.end());

    vector<LL> sum(k), cnt(k);
    calc(keypairs, 0, k, nodes, root, sum, cnt, 0, 0);

    vector<double> ans(k);
    for(int i=0; i<k; ++i) ans[keypairs[i].second] = (double)sum[i]/cnt[i];

    for(int i=0; i<k; ++i) cout << fixed << setprecision(10) << ans[i] << endl;
}

int main()
{
    solve();
}

// TLE when n=10^6
