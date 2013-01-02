// dfs
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int M = 1e7;
bool isprime[M+5];
int primes[M+5]; // primes[i] is num of primes less than i
int password[360][360];
int done[360][360];

void init()
{
    for (int i=0; i<=M; ++i) isprime[i] = true;
    isprime[0] = isprime[1] = false;
    for (int i=2; i<=M; ++i) if (isprime[i]) {
        for (int j=i+i; j<=M; j+=i) isprime[j] = false;
    }
    primes[0] = primes[1] = 0;
    for (int i=2; i<=M; ++i) {
        primes[i] = primes[i-1] + isprime[i-1];
    }
}

bool inbound(int r, int c, int N)
{
    return 0<=r && r<N && 0<=c && c<N;
}

void dfs(int r, int c, int bit, int N)
{
    done[r][c] = 1;
    int d[][2] = { {-1,0}, {0,+1}, {+1,0}, {0,-1} };
    for (int x=0; x<4; ++x) {
        int r2, c2;
        r2 = r + d[x][0];
        c2 = c + d[x][1];

        if (inbound(r2,c2,N) &&
            (password[r2][c2] - password[r][c])%2 == 0 &&
            !done[r2][c2]) {
            int p1, p2;
            p1 = password[r][c];
            p2 = password[r2][c2];
            //assert(p1<=M && p2<=M);
            if (0<=p1 && p1<=M && 0<=p2 && p2<=M &&
                !isprime[p1] && !isprime[p2])
                dfs(r2, c2, bit, N);
            }
    }
}

void solve()
{
    int N; scanf("%d", &N);
    for (int i=0; i<N; ++i)
    for (int j=0; j<N; ++j)
        scanf("%d", &password[i][j]);

    long long ans = 0;
    memset(done, 0, sizeof done);
    for (int i=0; i<N; ++i)
    for (int j=0; j<N; ++j) if (!done[i][j]) {
        int p = password[i][j];
        if (isprime[p]) ans += primes[p];
        else if (p % 2 == 0) {
            ans += p/2;
            dfs(i, j, 0, N);
        } else {
            ans += (p+1)/2 + 1;
            dfs(i, j, 1, N);
        }
    }
    cout << ans << endl;
}

int main()
{
    init();
    int T; scanf("%d", &T);
    while (T--)
        solve();
}

// RE ?
