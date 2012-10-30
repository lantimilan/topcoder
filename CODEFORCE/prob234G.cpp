// =========================================================
// 
//       Filename:  prob234G.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 01:53:54 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <fstream>
using namespace std;

int mylog(int n)
{
    int l=0;
    while((1<<l) < n)
        l++;
    return l;
}

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n; fin >> n;
    int l = mylog(n);
    fout << l << "\n";
    int up = 1<<l;
    for(int block=up/2; block > 0; block/=2) {
        int left[1024];
        int cnt=0;
        int val=0;
        for(int k=0; k<up/block; ++k) {
            for(int x=0; x<block; ++x) {
                ++val;
                if (k%2==0 && val <= n)
                    left[cnt++] = val;
            }
        }
        fout << cnt;
        for(int i=0; i<cnt; ++i)
            fout << " " << left[i];
        fout << endl;
    }
}
