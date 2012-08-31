// =========================================================
// 
//       Filename:  prob186C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/04/2012 08:55:42 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/04/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

const int MOD=1000000000+7;

int add(int a, int b)
{
    return ((int64)a+b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a*b % MOD;
}

int main()
{
    int64 n; cin >> n;
    int mat[2][2]={{3,1}, {1,3}};
    int ans[2][2]={{1,0}, {0,1}};

    // mat^n
    while(n) {
        int tmp[2][2]; 
        memset(tmp, 0, sizeof tmp);
        if (n&1) {
            for(int i=0; i<2; ++i)
            for(int j=0; j<2; ++j)
            for(int k=0; k<2; ++k)
                tmp[i][j] = add(tmp[i][j], mult(ans[i][k], mat[k][j]));
            for(int i=0; i<2; ++i)
            for(int j=0; j<2; ++j)
                ans[i][j] = tmp[i][j];
        }
        memset(tmp, 0, sizeof tmp);
        for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
        for(int k=0; k<2; ++k)
            tmp[i][j] = add(tmp[i][j], mult(mat[i][k], mat[k][j]));
        for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
            mat[i][j] = tmp[i][j];
        n/=2;
    }
    int res=ans[0][0];
    cout << res << endl;
}
