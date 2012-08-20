// =========================================================
// 
//       Filename:  smooth.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/20/2012 12:22:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/20/2012, LI YAN
// 
// =========================================================

// given NxN matrix A
// output NxN matrix B such that B[i][j] is avg over A[i2][j2] around (i,j)
// with KxK submatrix
//
// if K is odd, then the submatrix is (K-1)/2 x (K-1)/2
// if K is even, then upleft is K/2 x K/2 and lowright is (K/2-1)x(K/2-1)
//
// use integer division, upleft is always K/2, lowright is always (K-1)/2
//
// algorithm runs in O(N^2)
// idea is to move submatrix left to right, row by row

#include <algorithm>
#include <cstdio>
using namespace std;

int N, K;
int A[5005][5005];
int B[5005][5005];
int C[5005][5005]; // column prefix sum
double D[5005][5005]; // final answer

int get(int mat[][5005], int i, int j)
{
    if (0<=i && i<N && 0<=j && j<N)
        return mat[i][j];
    return 0;
}

void smooth()
{
    // calc C
    for(int j=0; j<N; ++j) {
        C[0][j] = A[0][j];
        for(int i=1; i<N; ++i) {
            C[i][j] = C[i-1][j] + A[i][j];
        }
    }
    // calc (0,0)
    for(int i=0; i<=(K-1)/2; i++)
    for(int j=0; j<=(K-1)/2; j++)
        B[0][0] += A[i][j];

    for(int i=0; i<N; ++i) {
        // the 0-th column
        if (i>0) {
            B[i][0] = B[i-1][0];
            for(int j=0; j<=(K-1)/2; j++) {
                B[i][0] -= get(A, i-K/2-1, j);
                B[i][0] += get(A, i+(K-1)/2, j);
            }
        }
        for(int j=1; j<N; ++j) {
            B[i][j] = B[i][j-1];
            int left, right;
            left = get(C, i+(K-1)/2, j-K/2-1) - get(C, i-K/2-1, j-K/2-1);
            right = get(C, i+(K-1)/2, j+K/2-1) - get(C, i-K/2-1, j+K/2-1);
            B[i][j] += right - left;
        }
    }

    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
    {
        int width = min(N-1, i+(K-1)/2) - max(0, i-K/2) + 1;
        int height = min(N-1, j+(K-1)/2) - max(0, j-K/2) + 1;
        int size = width * height;
        D[i][j] = 1.0 * B[i][j] / size;
    }

    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            printf("%.2f ", D[i][j]);
        }
        putchar('\n');
    }
}

int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        scanf("%d", &A[i][j]);
}
