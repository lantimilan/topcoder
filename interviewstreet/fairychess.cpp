// fairychess.cpp
//
//
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000000+7;
int sum[205][205][205]; // step, row, col
int edge[205][205][5]; // row, col, 0,1,2,3

char board[205][205];

void solve()
{
    int N, M, S; scanf("%d %d %d ", &N, &M, &S); //printf("N %d M %d S %d\n", N, M, S);
    for(int i=0; i<N; ++i) { gets(board[i]); } // puts(board[i]); }
    memset(sum[0], 0, sizeof sum);
    memset(edge, 0, sizeof edge);

    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        if (board[i][j]=='L') sum[0][i][j]=1;

    for(int step=1; step<=M; ++step) {
        // calc edge[0..1] from top to bottom
        // row[0]
        int i=0;
        for(int j=0; j<N; ++j) {
            if (j-S>=0) edge[i][j][0]=sum[step-1][i][j-S];
            if (j+S<N)  edge[i][j][1]=sum[step-1][i][j+S];
        }
        for(int i=1; i<N; ++i) {
            // do j=0 and j=N-1 separately
            // j=0, edge[0]
            int j=0;
            if (i-S>=0) edge[i][j][0] = sum[step-1][i-S][j];
            // j=N-1, edge[1]
            j=N-1;
            if (i-S>=0) edge[i][j][1] = sum[step-1][i-S][j];
            // j=0, edge[1]
            j=0;
            long long t=0;
            for(int ii=i, jj=S; ii>=0 && jj>=0; --ii, --jj) {
                //refadd(edge[step][i][j][1], sum[step-1][ii][jj]);
                t+=sum[step-1][ii][jj];
            }
            edge[i][j][1]=t%MOD;
            // j=N-1, edge[0]
            j=N-1;
            t=0;
            for(int ii=i, jj=j-S; jj<N; --ii, ++jj) if (ii>=0 && jj>=0) {
                //refadd(edge[step][i][j][0], sum[step-1][ii][jj]);
                t+=sum[step-1][ii][jj];
            }
            edge[i][j][0]=t%MOD;

            for(int j=1; j+1<N; ++j) {
                //int diff=0;
                //if (i-1-S>=0) refsub(diff, sum[step-1][i-1-S][j+1]);
                //if (j-S>=0)   refadd(diff, sum[step-1][i][j-S]);
                //edge[step][i][j][0] = add(edge[step][i-1][j+1][0], diff);
                //diff=0;
                //if (i-1-S>=0) refsub(diff, sum[step-1][i-1-S][j-1]);
                //if (j+S<N) refadd(diff, sum[step-1][i][j+S]);
                //edge[step][i][j][1] = add(edge[step][i-1][j-1][1], diff);
                long long t=0;
                if (i-1-S>=0) t+=MOD-sum[step-1][i-1-S][j+1];
                if (j-S>=0)   t+=sum[step-1][i][j-S];
                t+=edge[i-1][j+1][0];
                edge[i][j][0] = t%MOD;
                t=0;
                if (i-1-S>=0) t+=MOD-sum[step-1][i-1-S][j-1];
                if (j+S<N) t+=sum[step-1][i][j+S];
                t+=edge[i-1][j-1][1];
                edge[i][j][1] = t%MOD;
            }
        }

        // calc edge[2..3] from bottom to top
        // row[N-1]
        i=N-1;
        for(int j=0; j<N; ++j) {
            if (j-S>=0) edge[i][j][2]=sum[step-1][i][j-S];
            if (j+S<N)  edge[i][j][3]=sum[step-1][i][j+S];
        }
        for(int i=N-2; i>=0; --i) {
            // do j=0 and j=N-1 separately
            // j=0, edge[2]
            int j=0;
            if (i+S<N) edge[i][j][2] = sum[step-1][i+S][j];
            j=N-1;
            // j=N-1, edge[3]
            if (i+S<N) edge[i][j][3] = sum[step-1][i+S][j];
            // j=0, edge[3]
            j=0;
            long long t=0;
            for(int ii=i+S, jj=0; ii>=i; --ii, ++jj) if (ii<N && jj<N) {
                //refadd(edge[step][i][j][3], sum[step-1][ii][jj]);
                t+=sum[step-1][ii][jj];
            }
            edge[i][j][3]=t%MOD;
            // j=N-1, edge[2]
            j=N-1;
            t=0;
            for(int ii=i+S, jj=N-1; ii>=i; --ii, --jj) if (ii<N && jj>=0) {
                //refadd(edge[step][i][j][2], sum[step-1][ii][jj]);
                t+=sum[step-1][ii][jj];
            }
            edge[i][j][2]=t%MOD;

            for(int j=1; j+1<N; ++j) {
                //int diff=0;
                //if (i+1+S<N) refsub(diff, sum[step-1][i+1+S][j+1]);
                //if (j-S>=0)  refadd(diff, sum[step-1][i][j-S]);
                //edge[step][i][j][2] = add(edge[step][i+1][j+1][2], diff);
                long long t=0;
                if (i+1+S<N) t+=MOD-sum[step-1][i+1+S][j+1];
                if (j-S>=0)  t+=sum[step-1][i][j-S];
                t+=edge[i+1][j+1][2];
                edge[i][j][2] = t%MOD;


                //diff=0;
                //if (i+1+S<N) refsub(diff, sum[step-1][i+1+S][j-1]);
                //if (j+S<N)   refadd(diff, sum[step-1][i][j+S]);
                //edge[step][i][j][3] = add(edge[step][i+1][j-1][3], diff);
                t=0;
                if (i+1+S<N) t+=MOD-sum[step-1][i+1+S][j-1];
                if (j+S<N)   t+=sum[step-1][i][j+S];
                t+=edge[i+1][j-1][3];
                edge[i][j][3] = t%MOD;
            }
        }

        // calc sum[0][0]
        long long t=0;
        for(int i=0; i<=S; ++i)
            for(int j=0; j<=S-i; ++j) if (i<N && j<N) {
                //refadd(sum[step][0][0], sum[step-1][i][j]);
                t+=sum[step-1][i][j];
            }
        sum[step][0][0]=t%MOD;
        for(int j=1; j<N; ++j) { // row[0]
            //sum[step][0][j] = sum[step][0][j-1];
            //refsub(sum[step][0][j], edge[step][0][j-1][2]); // move of a triangle
            //refadd(sum[step][0][j], edge[step][0][j][3]);
            long long t=sum[step][0][j-1];
            t+=MOD-edge[0][j-1][2];
            t+=edge[0][j][3];
            sum[step][0][j]=t%MOD;
        }

        for(int i=1; i<N; ++i) {
            for(int j=0; j<N; ++j) {
            /*
                int diff=0;
                if (i-1-S>=0) refadd(diff, sum[step-1][i-1-S][j]);
                if (i+S<N)    refsub(diff, sum[step-1][i+S][j]);
                sum[step][i][j] = add(sum[step][i-1][j], diff);
                refsub(sum[step][i][j], edge[step][i-1][j][0]); // move of a diamond
                refsub(sum[step][i][j], edge[step][i-1][j][1]);
                refadd(sum[step][i][j], edge[step][i][j][2]);
                refadd(sum[step][i][j], edge[step][i][j][3]);
                */
                long long t=0;
                if (i-1-S>=0) t+=sum[step-1][i-1-S][j];
                if (i+S<N)    t+=MOD-sum[step-1][i+S][j];
                t+=sum[step][i-1][j];
                t+=MOD-edge[i-1][j][0]; // move of a diamond
                t+=MOD-edge[i-1][j][1];
                t+=edge[i][j][2];
                t+=edge[i][j][3];
                sum[step][i][j]=t%MOD;
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

    //int ans=0;
    long long ans=0;
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        //refadd(ans, sum[M][i][j]);
        ans+=sum[M][i][j];

    printf("%d\n", ans%MOD); // this gets a warning in compiling, but necessary to work on interviewstreet server, try use (int)ans%MOD with %d, or ans%MOD with %lld both FAIL
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// had the correct algorithm long ago but 
// to implement it within TLE requires more work
// 1. mod takes time, use it as few as possible
// 2. edge[] used to be an array with edge[step][i][j][0..3] but it is stupid because you never need edge[] array beyond current step
// these two make it pass

// #    Status  Signal  Time
// 1    Passed  Your code produced correct output for this testcase.    0.952059
// 2    Passed  Your code produced correct output for this testcase.    2.49216
// 3    Passed  Your code produced correct output for this testcase.    5.60835
// 4    Passed  Your code produced correct output for this testcase.    8.58054
// 5    Passed  Your code produced correct output for this testcase.    10.5327
// 6    Passed  Your code produced correct output for this testcase.    12.0328
// 7    Passed  Your code produced correct output for this testcase.    14.9889
// 8    Passed  Your code produced correct output for this testcase.    17.2651
