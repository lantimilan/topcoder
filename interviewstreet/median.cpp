// =========================================================
// 
//       Filename:  median.cpp
// 
//    Description:  online median
// 
//        Version:  1.0
//        Created:  06/14/2012 11:52:56 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/14/2012, LI YAN
// 
// =========================================================

// could also use balanced BST
//
// use two heap, one minheap, one maxheap with size diff at most 1
// use multi_set to keep track of all elements in current set
//
// if add: print median
// else delete: if found: print median; else print Wrong
//
//

#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
using namespace std;

typedef long long int64;
priority_queue<int64> pqmin, pqmax;
multiset<int64> nums, delmin, delmax;
int Nmin, Nmax;

void clean()
{
    multiset<int64>::iterator it;
    // clean up max
    while((it=delmax.find(pqmax.top())) != delmax.end()) {
        pqmax.pop();
        delmax.erase(it);
    }
    // clean up min
    while((it=delmin.find(pqmin.top())) != delmin.end()) {
        pqmin.pop();
        delmin.erase(it);
    }
}

void solve()
{
    char op;
    int64 k; 
    scanf("%c %lld ", &op, &k); //printf("%c %d\n", op, k);

    if (op=='a') { // add
        nums.insert(k);
        if (pqmax.empty() || k<=pqmax.top()) {
            pqmax.push(k); Nmax++;
        }
        else {
            pqmin.push(-k); Nmin++;
        }
        // balance size
        if (Nmax > Nmin+1) {
            int64 t = pqmax.top();
            pqmax.pop(); Nmax--;
            pqmin.push(-t); Nmin++;
        }
        else if (Nmin>Nmax) {
            int64 t = pqmin.top();
            pqmin.pop(); Nmin--;
            pqmax.push(-t); Nmax++;
        }
    }
    else { // erase
        assert(op=='r');
        multiset<int64>::iterator it=nums.find(k);
        if (it==nums.end()) { puts("Wrong!"); return; }
        nums.erase(it);
        if (k<=pqmax.top()) {
            Nmax--; delmax.insert(k);
            if (Nmax < Nmin) {
                int64 t = pqmin.top();
                pqmax.push(-t); Nmax++;
                pqmin.pop(); Nmin--;
            }
        }
        else {
            Nmin--; delmin.insert(-k);
            if (Nmax > Nmin+1) {
                int64 t = pqmax.top();
                pqmin.push(-t); Nmin++;
                pqmax.pop(); Nmax--;
            }
        }
    }
    clean(); 
    if (Nmax==0) assert(pqmin.empty() && pqmax.empty());
    if (Nmax<=0) { puts("Wrong!"); return; }
    // output
    /*
    if (nums.size()<=10000) { // use naive
        int s=nums.size();
        multiset<int64>::iterator it;
        int i;
        if (s&1) {
            for(it=nums.begin(), i=0; i+1<(s+1)/2; i++, it++);
            printf("%lld\n", *it);
        }
        else {
            for(it=nums.begin(), i=0; i+1<s/2; i++, it++);
            int64 a, b;
            a=*it; b=*++it;
            if ((a+b) &1) printf("%lld.5\n", (a+b)/2);
            else printf("%lld\n", (a+b)/2);
        }
        return;
    }
    */
    if (Nmax > Nmin) {
        int64 ans=pqmax.top();
        printf("%lld\n", ans);
    }
    else {
        int64 a=pqmax.top(), b=pqmin.top();
        int64 sum = int64(a)-b;
        if (sum==-1) printf("-0.5\n");
        else if (sum&1) printf("%lld.5\n", sum/2);
        else printf("%lld\n", sum/2);
    }
}

int main()
{
    Nmax=Nmin=0;
    int n; scanf("%d ", &n);
    for(int i=0; i<n; ++i) solve();
}

// 10/10 passed
// fixed:
// need int64 when input is INT_MIN -(2^32-1)
// tricky case, when a+b=-1, then 0 does not carry minus sign
//
// debug: use trivial algorithm to ensure major algorithm unlikely to fail
// 7/10 Passed
// Case 4,5,6 failed
