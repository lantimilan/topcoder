// =========================================================
// 
//       Filename:  prob1B.cpp
// 
//    Description:  B. Spreadsheets
// 
//        Version:  1.0
//        Created:  03/13/2011 10:45:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/13/2011, LI YAN
// 
// =========================================================

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

// R1C1 -> A1
string int2code(string str)
{
    //cout << "int2code " << str << endl;
    string rstr, cstr;
    int pos;
    for(pos=0; str[pos]!='C'; pos++) ;
    
    rstr = str.substr(1,pos-1); cstr = str.substr(pos+1);
    int k=0;
    for(int i=0; i<int(cstr.size()); ++i) k = k*10 + cstr[i]-'0';
    //cout << "k " << k << endl;
    int s,n,f;
    for(n=1,s=0,f=26; s<k; ++n, f*=26) s+=f;
    --n; f/=26; // s= 26+26^2+...+26^n >= k, f=26^n
    k -= (s-f); f/=26;

    string colstr(n,'A');
    for(int i=0; i<n; ++i, f/=26)
    { colstr[i] = (k-1)/f+'A'; k -= (k-1)/f*f; } // AZZZ can accomodate 26^3, +1 will be BAAA
        
    string res = colstr + rstr;
    return res;
}

// A1 -> R1C1
string code2int(string str)
{
    //cout << "code2int " << str << endl;
    int pos;
    for(pos=0; 'A' <= str[pos] && str[pos] <= 'Z'; ++pos) ;
    string rstr, cstr;
    rstr = str.substr(pos); cstr = str.substr(0,pos);
    int n = cstr.size();
    int k = 0;
    int f = 26;
    for(int i=0; i < n-1; ++i, f*=26) { k += f; }
    f/=26;
    for(int i=0; i < n; ++i, f/=26) { k += (cstr[i]-'A')*f + (f==1); }
    char buf[100]; sprintf(buf, "%d", k);
    string res = "R" + rstr + "C" + string(buf);
    return res;
}

void solve()
{
    string str; cin >> str;
    bool isRC = false;
    if (str[0] == 'R' && isdigit(str[1]))
        for(int k=2; k < int(str.size()); ++k)
            if (str[k] == 'C') { isRC=true; break; }
    string res;
    if (isRC) res = int2code(str);
    else res = code2int(str);

    cout << res << endl;
}
int main()
{
    int n; cin >> n;
    for(int i=0; i < n; ++i)
        solve();
}
/* *********
 * Mon Mar 14 01:42:51 PDT 2011
 * I don't like this solution, it ACed because I have created many test cases
 * and adjusted several off-by-one errors. Is there a clean way to do this?
 * Someone mentioned this conversion is ugly because letter 'A' is used as zero
 * when not in leading position and as 1 when is in the leading position.
 *
 * 336667   Mar 14, 2011 11:42:01 AM    lantimilan  1B - Spreadsheet    GNU C++
 * Accepted     920 ms  1400 KB 
 * */
