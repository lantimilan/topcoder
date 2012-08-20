#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std; 

#define DEBUG(x) cout << '>' << #x << ':' << x << endl;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
inline bool EQ(double a, double b) { return fabs(a-b) < 1e-9; }

const int INF = 1<<29;
typedef long long ll;

inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }

template<class T> void chmax(T & a, const T & b) { a = max(a, b); }
template<class T> void chmin(T & a, const T & b) { a = min(a, b); }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

const double EPS = 1e-9;
const int MAX = 1000;
int N, M;
double mat[MAX][MAX];

void output()
{
REP(i, N+1)
{
REP(j, N+M+1)
printf("%.2lf ", mat[i][j]);
printf("\n");
}
printf("\n");
}

int main()
{
scanf("%d%d", &N, &M);
REP(i, M)
{
int a, b;
scanf("%d%d", &a, &b);
--a, --b;
mat[a][i] = mat[b][i] = 1.0;
mat[N][i] = -1.0;
}
REP(i, N)
{
mat[i][M+i] = 1.0;
mat[i][M+N] = 1.0;
}
//output();

while (true)
{
int col = -1;
REP(i, M+N)
if (mat[N][i] < -EPS && (col == -1 || mat[N][i] < mat[N][col]))
col = i;
if (col == -1) break;

int row = -1;
REP(i, N)
{
if (EQ(mat[i][col],0.0))
continue;
if (EQ(mat[i][N+M],0.0) && mat[i][col] < -EPS)
continue;
if (mat[i][N+M] / mat[i][col] >= -EPS && (row == -1 || mat[i][N+M] / mat[i][col] < mat[row][N+M] / mat[row][col]))
row = i;
}

double mul = 1.0 / mat[row][col];
REP(i, M+N+1) mat[row][i] *= mul;
REP(i, N+1)
{
if (i == row) continue;
mul = -mat[i][col];
REP(j, N+M+1)
mat[i][j] += mul * mat[row][j];
}
//output();
}
printf("%.5lf\n", mat[N][N+M]);

return 0;
}
