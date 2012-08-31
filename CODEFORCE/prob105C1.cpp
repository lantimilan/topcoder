///////////////////////////////////////////////////
// http://codeforces.com/contest/105/problem/C
//
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct item_t {
    string name;
    int size;
    int atk, def, res;
};

void solve()
{
    int n; cin >> n;
    vector<item_t> weapon, armor, orb;
    map<string, pair<int,int> > homes;
    string category;
    for(int i=0; i<n; ++i) {
        item_t item;
        cin >> item.name >> category 
            >> item.atk >> item.def >> item.res >> item.size;
        homes[item.name]=make_pair(item.size,0);
        if (category=="weapon") weapon.push_back(item);
        else if (category=="armor") armor.push_back(item);
        else if (category=="orb") orb.push_back(item);
        else assert(false);
    }
    int k; cin >> k;
    vector<pair<int,string> > gladiator, sentry, physician;
    map<string,bool> residents;
    map<string,string> prev;
    map<string,string> typemap;
    map<string,int> points;
    for(int i=0; i<k; ++i)
    {
        string name, type; int bonus; string home;
        cin >> name >> type >> bonus >> home; residents[name]=false;
        homes[home].second++; prev[name]=home; typemap[name]=type; points[name]=bonus;
        if (type=="gladiator") gladiator.push_back(make_pair(bonus,name));
        else if (type=="sentry") sentry.push_back(make_pair(bonus,name));
        else if (type=="physician") physician.push_back(make_pair(bonus,name));
        else { cout << type << endl; assert(false); }
    }
    // if all homes are tight, then no move is possible
    bool tight=true;
    for(map<string,pair<int,int> >::const_iterator cit=homes.begin(); cit!=homes.end(); ++cit)
    { //cout << "map " << cit->first << ' ' << cit->second.first << ' ' << cit->second.second << endl;
    if (cit->second.first > cit->second.second) { tight=false; break; } }

    int wid, aid, oid; wid=aid=oid=0;
    int ww, aa, oo; ww=aa=oo=0;
    vector<string> wvec, avec, ovec;
    if (tight) // all tight, no moves
    {
        for(size_t i=0; i<weapon.size(); ++i) {
            int curr = weapon[i].atk;
            for(map<string,string>::const_iterator cit=prev.begin(); cit!=prev.end(); ++cit)
            { if (cit->second==weapon[i].name && typemap[cit->first]=="gladiator") curr+=points[cit->first]; }
            if (curr > ww) { wid=i; ww=curr; }
        }
        for(size_t i=0; i<armor.size(); ++i) {
            int curr = armor[i].def;
            for(map<string,string>::const_iterator cit=prev.begin(); cit!=prev.end(); ++cit)
            { if (cit->second==armor[i].name && typemap[cit->first]=="sentry") curr+=points[cit->first]; }
            if (curr > aa) { aid=i; aa=curr; }
        }
        for(size_t i=0; i<orb.size(); ++i) {
            int curr = orb[i].res;
            for(map<string,string>::const_iterator cit=prev.begin(); cit!=prev.end(); ++cit)
            { if (cit->second==orb[i].name && typemap[cit->first]=="physician") curr+=points[cit->first]; }
            if (curr > oo) { oid=i; oo=curr; }
        }
        for(map<string,string>::const_iterator cit=prev.begin(); cit!=prev.end(); ++cit)
        { 
            if (cit->second==weapon[wid].name) wvec.push_back(cit->first);
            if (cit->second==armor[aid].name) avec.push_back(cit->first);
            if (cit->second==orb[oid].name) ovec.push_back(cit->first);
        }
    }
    else
    {
    sort(gladiator.begin(), gladiator.end());
    sort(sentry.begin(), sentry.end());
    sort(physician.begin(), physician.end());
    int kgla=gladiator.size(),ksen=sentry.size(),kphy=physician.size();

    // weapon
    for(size_t i=0; i<weapon.size(); ++i)
    {
        int curr=weapon[i].atk;
        for(int k=kgla-1,s=weapon[i].size; k>=0 && s>0; --k,--s)
            curr += gladiator[k].first;
        if (curr > ww) { wid=i; ww=curr; }
    }
    for(int k=kgla-1,s=weapon[wid].size; k>=0 && s>0; --k,--s)
    {
        string s=gladiator[k].second;
        wvec.push_back(s); residents[s]=true;
    }
    // armor
    for(size_t i=0; i<armor.size(); ++i)
    {
        int curr=armor[i].def;
        for(int k=ksen-1,s=armor[i].size; k>=0 && s>0; --k,--s)
            curr += sentry[k].first;
        if (curr > aa) { aid=i; aa=curr; }
    }
    for(int k=ksen-1,s=armor[aid].size; k>=0 && s>0; --k,--s)
    {
        string s=sentry[k].second;
        avec.push_back(s); residents[s]=true;
    }
    // orb
    for(size_t i=0; i<orb.size(); ++i)
    {
        int curr=orb[i].res;
        for(int k=kphy-1,s=orb[i].size; k>=0 && s>0; --k,--s)
            curr += physician[k].first;
        if (curr > oo) { oid=i; oo=curr; }
    }
    for(int k=kphy-1,s=orb[oid].size; k>=0 && s>0; --k,--s)
    {
        string s=physician[k].second;
        ovec.push_back(s); residents[s]=true;
    }
    // collect remaining residents
    int kweapon=wvec.size(), karmor=avec.size(), korb=ovec.size();
    for(map<string,bool>::iterator it=residents.begin(); it!=residents.end(); ++it)
    {
        if (it->second) continue;
        if (kweapon<weapon[wid].size) { wvec.push_back(it->first); kweapon++; it->second=true; }
        else if (karmor<armor[aid].size) { avec.push_back(it->first); karmor++; it->second=true; }
        else if (korb<orb[oid].size) { ovec.push_back(it->first); korb++; it->second=true; }
    }
    }
    cout << weapon[wid].name << ' ' << wvec.size();
    for(size_t i=0; i<wvec.size(); ++i) cout << ' ' << wvec[i];
    cout << endl;
    cout << armor[aid].name << ' ' << avec.size();
    for(size_t i=0; i<avec.size(); ++i) cout << ' ' << avec[i];
    cout << endl;
    cout << orb[oid].name << ' ' << ovec.size();
    for(size_t i=0; i<ovec.size(); ++i) cout << ' ' << ovec[i];
    cout << endl;
}

int main()
{
    solve();
}

/************************
609594  Aug 13, 2011 10:45:01 PM    lantimilan  C - Item World  GNU C++     Accepted    30 ms   1600 KB
609580  Aug 13, 2011 10:41:43 PM    lantimilan  C - Item World  GNU C++     Wrong answer on test 28     30 ms   1500 KB
609538  Aug 13, 2011 10:31:33 PM    lantimilan  C - Item World  GNU C++     Wrong answer on test 13     10 ms   1400 KB
609529  Aug 13, 2011 10:29:52 PM    lantimilan  C - Item World  GNU C++     Wrong answer on test 3  30 ms   1400 KB 
**************************/
