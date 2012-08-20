// circle summation
//
// matrix multiplication
///////////////////////////////

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=1000000007;
int DIM;

struct matrix {
    int a[55][55];
    int m, n;
    matrix() { m=n=DIM; memset(a, 0, sizeof a); }
};

inline int add(int a, int b)
{
    int ans = int(((long long)a+b) %MOD);
    return ans;
}

inline int sub(int a, int b)
{
    int ans=a-b;
    if (ans<0) ans+=MOD;
    return ans;
}

inline int mult(int a, int b)
{
    int ans = int((long long)a*b % MOD);
    return ans;
}

inline void setzero(matrix &mat)
{
    memset(mat.a, 0, sizeof mat.a);
}

void setunit(matrix &mat)
{
    assert(mat.m==mat.n);
    setzero(mat);
    for(int i=0; i<mat.m; ++i) mat.a[i][i]=1;
}

void setincr(matrix &mat, int id)
{
    setunit(mat);
    int p1=(id-1+DIM)%DIM;
    int p2=(id+1)%DIM;    
    mat.a[id][p1]=mat.a[id][p2]=1;    
}

void setdecr(matrix &mat, int id)
{
    setunit(mat);
    int p1=(id-1+DIM)%DIM;
    int p2=(id+1)%DIM;    
    mat.a[id][p1]=mat.a[id][p2]=-1;
}

void mult(const matrix &m1, const matrix &m2, matrix &m3)
{
    assert(m1.n==m2.m);
    int m=m1.m, n=m1.n, l=m2.n;
    setzero(m3);
    for(int i=0; i<m; ++i)
    for(int k=0; k<n; ++k)
    for(int j=0; j<l; ++j)
    {
        m3.a[i][j]=add(m3.a[i][j], mult(m1.a[i][k], m2.a[k][j]));
        //long long tmp=(long long)m1.a[i][k] * m2.a[k][j] %MOD;
        //tmp += m3.a[i][j]; tmp%=MOD; 
        //m3.a[i][j] = (int)tmp;
    }
}

void mult(const matrix &mat, const int invec[], int outvec[])
{    
    for(int i=0; i<DIM; ++i)
    {
        outvec[i]=0;
        for(int j=0; j<DIM; ++j)
        {
            outvec[i] = add(outvec[i], mult(mat.a[i][j], invec[j]));
            //long long tmp=(long long)mat.a[i][j] * invec[j] %MOD;
            //tmp += outvec[i]; tmp %=MOD;
            //outvec[i]=(int)tmp;            
        }
    }
}

void fastpow(const matrix &mat, int b, matrix &res)
{
    setunit(res);
    matrix base=mat;
    while(b) {
        matrix tmp=res;
        if (b&1) mult(base, tmp, res);
        tmp=base;
        mult(tmp, tmp, base);
        b/=2;
    }
}

void solve()
{
    int N, M; scanf("%d%d", &N, &M);
    DIM=N;
    int val[55];
    for(int i=0; i<N; ++i)
        scanf("%d", &val[i]);
    
    
    // O(N^2 log M)
    // construct matrix for child[0]
        matrix mat, tmp; setunit(mat);
        for(int k=0; k<N; ++k) {
            // add row[p-1] and row[p+1] to row[p]
            int p[3]={(k-1+N)%N, k, (k+1)%N};
            for(int j=0; j<N; ++j) {
                int &dest=mat.a[p[1]][j];
                dest = add(dest, mat.a[p[0]][j]);
                dest = add(dest, mat.a[p[2]][j]);
                //dest = int(((long long)dest+mat.a[p[0]][j])%MOD);
                //dest = int(((long long)dest+mat.a[p[2]][j])%MOD);
            }
        }
        fastpow(mat, M/N, tmp); mat=tmp;
        for(int k=0; k<M%N; ++k) {
            // add row[p-1] and row[p+1] to row[p]
            int p[3]={(k-1+N)%N, k%N, (k+1)%N};
            for(int j=0; j<N; ++j) {
                int &dest=mat.a[p[1]][j];
                dest = add(dest, mat.a[p[0]][j]);
                dest = add(dest, mat.a[p[2]][j]);
                //dest = int(((long long)dest+mat.a[p[0]][j])%MOD);
                //dest = int(((long long)dest+mat.a[p[2]][j])%MOD);
            }
        }

    for(int i=0; i<N; ++i) { // start from child[i]    
        // shift val[] by offset -i
        int currval[55];
        for(int k=0; k<N; ++k) {
            currval[(k-i+N)%N] = val[k];
        }
        
        int curr[55], ans[55];                
        mult(mat, currval, curr);

        // shift curr[] by offset +i
        for(int k=0; k<N; ++k) {
            ans[(k+i)%N] = curr[k];
        }

        for(int k=0; k<N; ++k) {
            if (k) putchar(' ');
            printf("%d", ans[k]);
        }
        putchar('\n');
    }
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t) {
        if (t) putchar('\n');        
        solve();
    }
}

// whether the function is inline or not does not make much difference
// [lyan@localhost interviewstreet]$ !time
// time ./a.out <circlesum_large.in >my.out
//
// real 0m3.527s
// user 0m3.431s
// sys  0m0.013s
//
// use add/sub/mult for interger arithmetic
// [lyan@localhost interviewstreet]$ !time
// time ./a.out <circlesum_large.in >my.out
//
// real 0m3.503s
// user 0m3.433s
// sys  0m0.016s
//
// use integer arithmetic
// [lyan@localhost interviewstreet]$ !time
// time ./a.out <circlesum_large.in >my.out
//
// real 0m2.992s
// user 0m2.917s
// sys  0m0.020s
//
//
// Submission Accepted
// 10/10 testcases passed
// 30 Point(s) 
//
// O(N^2 logM) runs in 2.983s
//
// O(N^3 logM) TLE runs in 2m
// 
// you can do O(N^2 logM)
//
// no help
// Time Limit Exceeded
// 2/10 testcases passed
// 6 Point(s) 
// too many left mult, right mult mistakes
//
//Time Limit Exceeded
//2/10 testcases passed
//6 Point(s) 
