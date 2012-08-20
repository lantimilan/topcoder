// fairychess.cpp
//
// tough problem because of P exists
// then cannot accumulate sum easily
//
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000000+7;
int sum[205][205][205]; // step, row, col
int edge[205][205][205][5]; // step, row, col, 0,1,2,3

char board[205][205];

int add(int a, int b)
{
    return ((long long)a+b)%MOD;
}

void refadd(int &a, int b)
{
    a = ((long long)a+b)%MOD;
}

void refsub(int &a, int b)
{
    a = ((long long)a-b+MOD)%MOD;
}

void solve()
{
    int N, M, S; scanf("%d %d %d ", &N, &M, &S); //printf("N %d M %d S %d\n", N, M, S);
    for(int i=0; i<N; ++i) { gets(board[i]); } // puts(board[i]); }
    memset(sum, 0, sizeof sum);
    memset(edge, 0, sizeof edge);

    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        if (board[i][j]=='L') sum[0][i][j]=1;

    for(int step=1; step<=M; ++step) {
        // calc edge[0..1] from top to bottom
        // row[0]
        int i=0;
        for(int j=0; j<N; ++j) {
            if (j-S>=0) edge[step][i][j][0]=sum[step-1][i][j-S];
            if (j+S<N)  edge[step][i][j][1]=sum[step-1][i][j+S];
        }
        for(int i=1; i<N; ++i) {
            // do j=0 and j=N-1 separately
            // j=0, edge[0]
            int j=0;
            if (i-S>=0) edge[step][i][j][0] = sum[step-1][i-S][j];
            // j=N-1, edge[1]
            j=N-1;
            if (i-S>=0) edge[step][i][j][1] = sum[step-1][i-S][j];
            // j=0, edge[1]
            j=0;
            for(int ii=i, jj=S; ii>=0 && jj>=0; --ii, --jj)
                refadd(edge[step][i][j][1], sum[step-1][ii][jj]);
            // j=N-1, edge[0]
            j=N-1;
            for(int ii=i, jj=j-S; jj<N; --ii, ++jj) if (ii>=0 && jj>=0)
                refadd(edge[step][i][j][0], sum[step-1][ii][jj]);

            for(int j=1; j+1<N; ++j) {
                int diff=0;
                if (i-1-S>=0) refsub(diff, sum[step-1][i-1-S][j+1]);
                if (j-S>=0)   refadd(diff, sum[step-1][i][j-S]);
                edge[step][i][j][0] = add(edge[step][i-1][j+1][0], diff);
                diff=0;
                if (i-1-S>=0) refsub(diff, sum[step-1][i-1-S][j-1]);
                if (j+S<N) refadd(diff, sum[step-1][i][j+S]);
                edge[step][i][j][1] = add(edge[step][i-1][j-1][1], diff);
            }
        }

        // calc edge[2..3] from bottom to top
        // row[N-1]
        i=N-1;
        for(int j=0; j<N; ++j) {
            if (j-S>=0) edge[step][i][j][2]=sum[step-1][i][j-S];
            if (j+S<N)  edge[step][i][j][3]=sum[step-1][i][j+S];
        }
        for(int i=N-2; i>=0; --i) {
            // do j=0 and j=N-1 separately
            // j=0, edge[2]
            int j=0;
            if (i+S<N) edge[step][i][j][2] = sum[step-1][i+S][j];
            j=N-1;
            // j=N-1, edge[3]
            if (i+S<N) edge[step][i][j][3] = sum[step-1][i+S][j];
            // j=0, edge[3]
            j=0;
            for(int ii=i+S, jj=0; ii>=i; --ii, ++jj) if (ii<N && jj<N)
                refadd(edge[step][i][j][3], sum[step-1][ii][jj]);
            // j=N-1, edge[2]
            j=N-1;
            for(int ii=i+S, jj=N-1; ii>=i; --ii, --jj) if (ii<N && jj>=0)
                refadd(edge[step][i][j][2], sum[step-1][ii][jj]);

            for(int j=1; j+1<N; ++j) {
                int diff=0;
                if (i+1+S<N) refsub(diff, sum[step-1][i+1+S][j+1]);
                if (j-S>=0)  refadd(diff, sum[step-1][i][j-S]);
                edge[step][i][j][2] = add(edge[step][i+1][j+1][2], diff);

                diff=0;
                if (i+1+S<N) refsub(diff, sum[step-1][i+1+S][j-1]);
                if (j+S<N)   refadd(diff, sum[step-1][i][j+S]);
                edge[step][i][j][3] = add(edge[step][i+1][j-1][3], diff);
            }
        }

        // calc sum[0][0]
        for(int i=0; i<=S; ++i)
            for(int j=0; j<=S-i; ++j) if (i<N && j<N)
                refadd(sum[step][0][0], sum[step-1][i][j]);

        for(int j=1; j<N; ++j) { // row[0]
            sum[step][0][j] = sum[step][0][j-1];
            refsub(sum[step][0][j], edge[step][0][j-1][2]); // move of a triangle
            refadd(sum[step][0][j], edge[step][0][j][3]);
        }

        for(int i=1; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                int diff=0;
                if (i-1-S>=0) refadd(diff, sum[step-1][i-1-S][j]);
                if (i+S<N)    refsub(diff, sum[step-1][i+S][j]);
                sum[step][i][j] = add(sum[step][i-1][j], diff);
                refsub(sum[step][i][j], edge[step][i-1][j][0]); // move of a diamond
                refsub(sum[step][i][j], edge[step][i-1][j][1]);
                refadd(sum[step][i][j], edge[step][i][j][2]);
                refadd(sum[step][i][j], edge[step][i][j][3]);
            }
        }

        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j) if (board[i][j]=='P') {
                sum[step][i][j]=0;
                //printf("%d ", sum[step][i][j]);
            }
        }
    }

    int ans=0;
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        refadd(ans, sum[M][i][j]);

    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// #    Status  Signal  Time
// 1    Passed  Your code produced correct output for this testcase.    2.77617
// 2    Failed  Your code exceeded the timelimit for this testcase.     6.00837
// 3    Failed  Your code exceeded the timelimit for this testcase.     9.25258
// 4    Failed  Your code exceeded the timelimit for this testcase.     12.4928
// 5    Failed  Your code exceeded the timelimit for this testcase.     15.721
// 6    Passed  Your code produced correct output for this testcase.    18.9332
// 7    Failed  Your code exceeded the timelimit for this testcase.     22.1734
// 8    Failed  Your code exceeded the timelimit for this testcase.     25.401
