// =========================================================
// 
//       Filename:  RRATING.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/01/2012 10:55:25 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <functional>
#include <queue>
using namespace std;

priority_queue<int,  vector<int>, greater<int> > upper;
priority_queue<int> lower;

int main()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        int op; scanf("%d", &op);
        if (op==1) {
            int x; scanf("%d", &x);
            if (lower.empty() || x<=lower.top()) lower.push(x);
            else upper.push(x);
            size_t size=upper.size()+lower.size();
            if (upper.size() > size/3) {
                int t = upper.top();
                upper.pop();
                lower.push(t);
            }
            else if (upper.size() < size/3) {
                int t = lower.top();
                lower.pop();
                upper.push(t);
            }
        }
        else {
            if (upper.empty()) puts("No reviews yet");
            else printf("%d\n", upper.top());
        }
    }
}
