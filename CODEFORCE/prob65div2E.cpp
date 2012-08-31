// =========================================================
// 
//       Filename:  prob65div22E.cpp
// 
//    Description:  E. Nuclear Fusion
// 
//        Version:  1.0
//        Created:  03/29/2011 09:56:57 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/29/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

const char *chems[] = {"", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm"};

int dp[20][1<<17];
int eqns[20];
vector<int> tbl[105];

int countone(int k)
{
    int res=0;
    while(k) { res++; k&=k-1; }
    return res;
}

bool same(int a, int b, const vector<int> &chemin)
{
    if (countone(a) != countone(b)) return false;
    int n = chemin.size();
    vector<int> avec, bvec;
    for(int i=0; i<n; ++i) 
    { 
        if (1<<i & b) { bvec.push_back(chemin[i]); }
        if (1<<i & a) { avec.push_back(chemin[i]); }
    }
    assert(avec.size() == bvec.size());
    sort(avec.begin(), avec.end());
    sort(bvec.begin(), bvec.end());

    for(int x=0; x<int(bvec.size()); ++x) 
        if (bvec[x] != avec[x]) { return false; }

    return true;
}

int knapsack(int k, int bits, const vector<int> &chemin, const vector<int> &chemout)
{
//cout << "knapsack " << k << " " << bits << endl;
    assert(k<int(chemout.size()));
    if (k<0) return 1;
    if (countone(bits) < 2*(k+1)) return 0; // every chemout[k] needs at least two from chemin[]
    if (dp[k][bits]>=0) return dp[k][bits];
    int n = chemin.size();
    if (k==0) 
    {
        int sum=0;
        for(int i=0; i<n; ++i) if (1<<i & bits) sum+=chemin[i];
        if (sum == chemout[k]) { eqns[k]=bits; return dp[k][bits]=1; }
        else return dp[k][bits]=0;
    }
    vector<int>::iterator it;
    int target = chemout[k];
    //int prev = -1;
    for(it=tbl[target].begin(); it!=tbl[target].end(); ++it)
    {
        int curr = *it; 
        if ((curr & ~bits) != 0) continue;
        //if (prev >=0 && same(prev,curr,chemin)) continue;
        if (knapsack(k-1,bits&~curr,chemin,chemout))
        { eqns[k] = curr; return dp[k][bits] = 1; }
        //prev = curr;
    }
    return dp[k][bits]=0;
}

void solve()
{
    map<string,int> lookup;
    for(int i=0; i<int(sizeof(chems)/sizeof(chems[0])); ++i) { string key=chems[i]; lookup[key]=i; }

    memset(dp, -1, sizeof dp);
    memset(eqns, -1, sizeof eqns);

    int n, k; cin >> n >> k;
    vector<int> chemin(n), chemout(k);

    string str;
    for(int i=0; i<n; ++i) { cin >> str; chemin[i]  = lookup[str]; }
    for(int i=0; i<k; ++i) { cin >> str; chemout[i] = lookup[str]; }
    sort(chemin.begin(), chemin.end(), greater<int>());
    sort(chemout.begin(), chemout.end(), greater<int>());

    vector<int> same;
    vector<int>::iterator it1, it2;
    for(it1=chemin.begin(), it2=chemout.begin(); it1!=chemin.end()&&it2!=chemout.end();)
    {
        if (*it1 == *it2) { same.push_back(*it1); it1=chemin.erase(it1); it2=chemout.erase(it2); }
        else if (*it1 >*it2) ++it1;
        else ++it2;
    }

    n = chemin.size(); k = chemout.size();
    for(int i=0; i<105; ++i) tbl[i].clear(); // can I use sizeof to get nelem here?
    for(int b=0; b<(1<<n); ++b)
    {
        int sum=0;
        for(int k=0; k<n; ++k) if (b&(1<<k)) sum+=chemin[k];
        if (sum <= 100) 
        {
// wrong: even if two bitmaps have same list of chem elems
// they can both be useful in tbl[]
            //if (diff(b, tbl[sum], chemin)) 
            tbl[sum].push_back(b);
        }
    }
    if (knapsack(k-1,(1<<n)-1, chemin, chemout))
    {
        cout << "YES\n";
        for(int i=0; i<int(same.size()); ++i)
        { string str = chems[same[i]]; cout << str << "->" << str << endl; }
        for(int i=0; i<k; ++i)
        {
            string target = chems[chemout[i]];
            vector<string> srcs;
            int bits = eqns[i];
            for(int b=0; b<n; ++b)
                if (1<<b & bits) { srcs.push_back(string(chems[chemin[b]])); }
            for(int x=0; x<int(srcs.size()); ++x)
            { 
                if (x) cout << "+" << srcs[x];
                else cout << srcs[x];
            }
            cout << "->" << target << endl;
        }
    }
    else
    {
        cout << "NO\n";
    }
}
int main()
{
    solve();
}

/* ******************
 * people are using DFS
 *
 * Some observation:
 * 1. if some elem appear both in chemin and chemout, then they form an eqn
 * 2. given that chemin and chemout are now disjoint, each chemout[j] must get
 * at least two elems from chemin[], now k is no more than 8
 * 3. since chemout[] has max elem no more than 100, we can build a tbl to look
 * up possible bitmaps from chemin[] to construct chemout[]
 * 4. since each bitmap that results in the same seq of elems are equivalent,
 * we only search non-equivalent bitmaps
 * 5. the essential step during the recursion call is to recurse only when 
 * curr is under bits
 *
 * item 4 saved a factor of 2, from 140ms to 50ms
 * 366847        Mar 30, 2011 11:08:00 AM   lantimilan        E - Nuclear Fusion
 * GNU C++       Accepted        140 ms      12500 KB 
 *
 * Finally got AC, but there must be a better algorithm without so many
 * optimization tricks.
 *
 * 366837        Mar 30, 2011 11:00:17 AM   lantimilan        E - Nuclear Fusion
 * GNU C++       Accepted        50 ms       12500 KB
 *
 * 366832   Mar 30, 2011 10:56:54 AM    lantimilan  E - Nuclear Fusion  GNU C++
 * Wrong answer on test 24  50 ms   12500 KB
 *
 * 366819   Mar 30, 2011 10:44:24 AM    lantimilan  E - Nuclear Fusion  GNU C++
 * Wrong answer on test 24  300 ms  11600 KB
 *
 * 366806   Mar 30, 2011 10:30:18 AM    lantimilan  E - Nuclear Fusion  GNU C++
 * Time limit exceeded on test 85   3000 ms     12500 KB
 *
 * tried a bunch of optimization to stop recursion early, still TLE
 * I am not using the right algorithm
 *
 * 366806        Mar 30, 2011 10:30:18 AM   lantimilan        E - Nuclear Fusion
 * GNU C++       Time limit exceeded on test 85      3000 ms     12500 KB 
 *
 * 366798        Mar 30, 2011 10:20:35 AM   lantimilan        E - Nuclear Fusion
 * GNU C++       Time limit exceeded on test 33      3000 ms     12500 KB
 *
 * 366796        Mar 30, 2011 10:16:26 AM   lantimilan        E - Nuclear Fusion
 * GNU C++       Time limit exceeded on test 33      3000 ms     12500 KB
 *
 * 366795   Mar 30, 2011 10:12:21 AM    lantimilan  E - Nuclear Fusion  GNU C++
 * Runtime error on test 9  50 ms   11600 KB 
 *
 * 366784        Mar 30, 2011 9:51:17 AM    lantimilan        E - Nuclear Fusion
 * GNU C++       Time limit exceeded on test 33      3000 ms     12500 KB 
 * */
