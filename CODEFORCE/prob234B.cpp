// =========================================================
// 
//       Filename:  prob234B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/16/2012 12:13:39 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/16/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

typedef pair<int,int> pii; // val, pos

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, k; fin >> n >> k;
    int light[1005];
    vector<pii> vec(n);
    for(int i=0; i<n; ++i) {
        fin >> light[i];
        vec[i] = pii(light[i], i);
    }

    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    int minval = vec[k-1].first;
    fout << minval << endl;
    for(int i=0; i<k; ++i) {
        if (i) fout << " ";
        fout << vec[i].second+1;
    }
    fout << endl;
}
