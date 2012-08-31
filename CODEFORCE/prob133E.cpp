// =========================================================
// 
//       Filename:  prob133E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/14/2011 10:52:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/14/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
using namespace std;

struct Node {
    int pos, index, change, dir;
    Node() { pos=index=change=dir=0; }
    Node(int a, int b, int c, int d) { pos=a; index=b; change=c; dir=d; }
};

bool operator<(const Node &n1, const Node &n2)
{
    if (n1.pos != n2.pos) return n1.pos<n2.pos;
    if (n1.index != n2.index) return n1.index<n2.index;
    if (n1.change != n2.change) return n1.change<n2.change;
    return n1.dir < n2.dir;
}

char cmd[105];
set<Node> nodes;
int N;

void dfs(Node start)
{
    nodes.insert(start);
    int index=start.index;
    int change=start.change;
    int dir=start.dir;

    if (index>=N) return;

    if (cmd[index]=='T') {
        Node next=start;
        next.index++; next.dir=-dir;
        if (nodes.find(next) == nodes.end()) dfs(next);
        if (change) {
            next=start;
            next.pos+=dir;
            next.index++;
            next.change--;
            if (nodes.find(next) == nodes.end()) dfs(next);
        }
    }
    else { // cmd is 'F'
        Node next=start;
        next.pos += dir;
        next.index++;
        if (nodes.find(next) == nodes.end()) dfs(next);
        if (change) {
            next=start;
            next.index++;
            next.change--;
            next.dir=-dir;
            if (nodes.find(next) == nodes.end()) dfs(next);
        }
    }
}

int main()
{
    gets(cmd); N=strlen(cmd);
    int change; scanf("%d", &change);

    int best=0;
    for(int cc=change; cc>=0; cc-=2) {
    //nodes.clear();
    Node start(0,0,cc,+1);
    dfs(start);

    set<Node>::const_iterator cit;
    for(cit=nodes.begin(); cit!=nodes.end(); ++cit) 
    if (cit->change==0 && cit->index==N)
    {
        int curr = abs(cit->pos);
        best = max(best, curr);
    }
    }
    printf("%d\n", best);
}

// 956040   Dec 15, 2011 11:17:26 AM    lantimilan  E - Logo Turtle     GNU C++
// Accepted     420 ms  11300 KB
//
// stupid erase all set nodes discovered already
// 956035   Dec 15, 2011 11:13:47 AM    lantimilan  E - Logo Turtle     GNU C++
// Time limit exceeded on test 4    2000 ms     7200 KB
//
// forgot to check every change-2*i
// 956033   Dec 15, 2011 11:11:18 AM    lantimilan  E - Logo Turtle     GNU C++
// Wrong answer on test 4   170 ms  7200 KB
