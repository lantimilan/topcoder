// =========================================================
// 
//       Filename:  prob7E.cpp
// 
//    Description:  http://codeforces.com/contest/7/problem/E
// 
//        Version:  1.0
//        Created:  08/12/2011 09:10:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/12/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <utility>

using namespace std;

#define sz(a) int(a.size())

map<string,string> macros;
vector<string> macronames;

struct triple_t {
    int lop, lpos, ops;
};

struct node_t {
    int lop, lpos, ops, rpos, rop; // 1,2,4,8 //+,-,*,/
};

string safestr, unsafestr;

//string macrosub(const string &text, bool issafe)
void macrosub(const string &text, bool issafe, string& ans)
{
    string prev, str; prev=text;
    int K=macronames.size();
    for(int k=K-1; k>=0; --k)
    {
    str=""; string val=macros[macronames[k]];
    for(int i=0; i<sz(prev); )
    {
        if (isalpha(prev[i])) { // grab a name
            int begin=i;
            for(; i<sz(prev) && isalpha(prev[i]); ++i);
            string name=prev.substr(begin,i-begin);
            if (macronames[k]==name) {
                if (issafe) str += "(" + val + ")";
                else str += val;
            }
            else str += name;
        }
        else str += prev[i++];
    }
    prev=str;
    }
    //cout << "macrosub: " << str << endl;
    //return str;
    ans=str;
}

bool isop(char ch) { return ch=='+'||ch=='-'||ch=='*'||ch=='/'; }

void deparen(string &str)
{
//cout << "before " << str << endl;
    stack<triple_t> st; // lpos, lop, ops
    vector<node_t> vec; // lop, lpos, ops, rpos, rop, 1+ 2- 4* 8/

    int lop=0;
    for(int i=0; i<sz(str); ++i)
    {
        char ch = str[i];
        if (ch == '(') {
            triple_t tt; tt.lpos=i; tt.lop=lop; tt.ops=0;
            st.push(tt); lop=0;
        }
        else if (ch == ')') { assert(!st.empty());
            node_t node; node.lpos = st.top().lpos; node.lop=st.top().lop; 
            node.ops=st.top().ops;
            st.pop();
            node.rpos=i; node.rop=0;
            vec.push_back(node);
        }
        else if (isop(ch)) {
            string strops="+-*/"; int iop; // CAREFUL, remove this space between * and /
            for(iop=0; iop<sz(strops); ++iop) if (ch == strops[iop]) break;
            assert(iop < sz(strops)); 
            lop=1<<iop; if (!vec.empty() && vec.back().rop==0) vec.back().rop=1<<iop;
            if (!st.empty()) st.top().ops|=1<<iop;
        }
    }
    
    // deal with nested parens
    bool nested=false;
    //cout << "str: " << str << endl;
    for(int i=0; i<sz(vec); ++i)
    {
        //cout << str << ": " << vec[i].lpos << ' ' << vec[i].ops << ' ' << vec[i].rpos 
        //    << ' ' << vec[i].lop << ' ' << vec[i].rop << endl;
        if (vec[i].ops==0) {
            str[vec[i].lpos]=str[vec[i].rpos]=' ';
            nested=true;
        }
    }
    if (nested) { deparen(str); return; } // need to recalculte vec so the recursive call here
    
    // what about nested parens?
    //
    // when can remove parens, set ( and ) to space
    // 1. if ops has none
    // 2. if ops has only * and /, then lop can have + - * or none, rop can have +
    // - * / and none
    // 3. if ops has + or -, then lop can have + or none, rop can have + - or none
    for(int i=0; i<sz(vec); ++i)
    {
        assert(vec[i].ops);
        if ((vec[i].ops & 3) == 0) { // inner has no + -
            if (vec[i].lop!=8) { str[vec[i].lpos]=str[vec[i].rpos] = ' '; }
        }
        else { // inner has +,-
            if ((vec[i].lop&(2+4+8))==0 && (vec[i].rop&(4+8))==0)
                { str[vec[i].lpos]=str[vec[i].rpos] = ' '; }
        }
    }
//cout << "after " << str << endl;
}
void solve()
{
    macros.clear();
    int n; cin >> n; cin.ignore(1024,'\n'); // default for cin.ignore is EOF
    string line;
    for(int i=0; i<n; ++i)
    {
        getline(cin,line);
        const string &token="define";
        size_t p;
        for(p=0; p<line.size(); ++p) 
            if (line.substr(p,token.size())==token)
                break;
        string keyval = line.substr(p+token.size());
        //cout << keyval << endl;
        for(p=0; p<keyval.size() && keyval[p]==' '; ++p); // skip leading space
        assert(p<keyval.size()); int begin=p;
        for(; p<keyval.size() && keyval[p]!=' '; ++p); // get name
        string key = keyval.substr(begin,p-begin);
        string val = keyval.substr(p+1);
        macros[key]=val; //cout << "map: " << key << "*****" << val << endl;
        macronames.push_back(key);
    }

    string text; getline(cin,text); //cout << text << endl;

    // macro sub
    //safestr=macrosub(text, true);
    //unsafestr=macrosub(text, false);
    macrosub(text,true,safestr);
    macrosub(text,false,unsafestr);

    cout << "safe   sub: " << safestr << endl;
    cout << "unsafe sub: " << unsafestr << endl;

    deparen(safestr); deparen(unsafestr);
    cout << "safe deparen:   " << safestr << endl;
    cout << "unsafe deparen: " << unsafestr << endl;

    bool good=true;
    int i,j;
    for(i=0,j=0; i<sz(safestr) && j<sz(unsafestr); )
    { 
        if (safestr[i]==' ') ++i;
        else if (unsafestr[j]==' ') ++j;
        else if (safestr[i]!=unsafestr[j]) { good=false; break; }
        else ++i, ++j;
    }
    for(;i<sz(safestr) && safestr[i]==' '; ++i);
    for(;j<sz(unsafestr) && unsafestr[j]==' '; ++j);
    //cout << i << ' ' << j << endl;
    if (i<sz(safestr) || j<sz(unsafestr)) good=false;
    if (good) cout << "OK" << endl;
    else cout << "Suspicious" << endl;
}

int main()
{
    solve();
}

// for 100 macros with 
// aa = a + a + ... + a (30 terms)
// ab = aa + aa + ... + aa
// ...
// this results in a fully expanded expr with length 30^100, this is too much
// memory
// Fri Aug 12 23:47:52 PDT 2011
// 604694   Aug 13, 2011 10:46:06 AM    lantimilan  E - Defining Macros     GNU
// C++  Time limit exceeded on test 134     3000 ms     233400 KB 
