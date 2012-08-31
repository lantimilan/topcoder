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
#include <cstdio>
#include <iostream>
#include <map>
#include <stack>
#include <string>
using namespace std;

enum Token {
    Expr,
    Factor,
    Term,
    Suspicious
};

map<string,Token> def;
map<char,int> prec;

void init()
{
    prec['\0']=0;
    prec['+']=1;
    prec['-']=1;
    prec['*']=3;
    prec['/']=3;
}

template<int P(int)>
void skip(const char *&p)
{
    while(*p && P(*p)) 
        ++p;
}

Token parse(const char *&p)
{
    //cout << "parse:" << p << endl;
    stack<Token> vals;
    stack<char> ops;
    const char *q;
    while(true) {
        //cout << "while:" << p << endl;
        skip<isblank>(p);
        if (*p=='(') {
            ++p; // skip '('
            Token res = parse(p); //cout << "return:" << p << endl;
            if (res==Suspicious) vals.push(Suspicious);
            else vals.push(Expr);
            ++p; // skip ')'
        }
        else {
            q=p;
            skip<isalnum>(p);
            string id=string(q,p-q); 
            if (def.count(id)) vals.push(def[id]);
            else vals.push(Expr);
        }
        skip<isblank>(p); //cout << p << endl;
        // expects op
        while(!ops.empty() && prec[ops.top()] >= prec[*p]) {
            Token rhs = vals.top(); vals.pop();
            Token lhs = vals.top(); vals.pop();
            if (lhs==Suspicious || rhs==Suspicious) {
                vals.push(Suspicious);
            } else if (ops.top()=='+' || ops.top()=='-') {
                if (ops.top()=='-' && rhs==Term) vals.push(Suspicious);
                else vals.push(Term);
            } else if (ops.top()=='*' || ops.top()=='/') {
                if (lhs==Term || rhs==Term) vals.push(Suspicious);
                else if (ops.top()=='/' && rhs==Factor) vals.push(Suspicious);
                else vals.push(Factor);
            } else { cout << lhs << ' ' << ops.top() << ' ' << rhs << endl;  assert(false); }
            ops.pop();
        }
        if (*p=='\0' || *p==')') { return vals.top(); }
        else ops.push(*p++);
    }
}

int main()
{
    init();
    int n; scanf("%d", &n);
    char name[128], expr[128];
    const char *pname, *pexpr;
    for(int i=0; i<n; ++i)
    {
        scanf(" # define %s %[^\n]", name, expr);
        //cout << name << ' ' << expr << endl;
        def[pname=name]=parse(pexpr=expr);
    }
    scanf(" %[^\n]",expr); //cout << expr << endl;
    if (parse(pexpr=expr)==Suspicious) puts("Suspicious");
    else puts("OK");
}

// recursive parser
// the use of scanf
//
// 613538   Aug 17, 2011 10:40:00 AM    lantimilan  E - Defining Macros     GNU
// C++  Accepted    30 ms   1400 KB
// 613534   Aug 17, 2011 10:35:34 AM    lantimilan  E - Defining Macros     GNU
// C++  Runtime error on test 6     30 ms   1400 KB
// 613532   Aug 17, 2011 10:34:27 AM    lantimilan  E - Defining Macros     GNU
// C++  Wrong answer on test 1  10 ms   1400 KB
// 613523   Aug 17, 2011 10:28:26 AM    lantimilan  E - Defining Macros     GNU
// C++  Wrong answer on test 5  10 ms   1400 KB 
