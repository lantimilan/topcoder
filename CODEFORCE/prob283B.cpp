// prob283B.cpp
// must stop at a[1] regardless of what a[1] is
// because 1 <= a[1] <= n-1
// when sub a[1], x is 1 so x - a[x] <= 0
// if it is add a[1], then it is a loop

#include <iostream>
using namespace std;

const long long LOOP = 1LL<<60;

int a[200000+5];
int vis[200000+5][2];
long long yval[200000+5][2];
int last[200000+5][2];
int n;

void dfs(int pos, int hop)
{
    vis[pos][hop] = 1;
    if (pos == 1 && hop == 0) {
        yval[pos][hop] = LOOP;
        return;
    }
    if (hop == 0) {  // pos += a[pos]
        int next = pos + a[pos];
        if (next > n) {
            yval[pos][hop] = a[pos];
            last[pos][hop] = pos;
            return;
        } else {
            if (!vis[next][1-hop]) {
                dfs(next, 1-hop);
            } else {
                if (yval[next][1-hop] == 0)
                    yval[next][1-hop] = LOOP;
            }
            long long prev = yval[next][1-hop];
            if (prev == LOOP) {
                yval[pos][hop] = LOOP;
            } else {
                yval[pos][hop] = yval[next][1-hop] + a[pos];
                last[pos][hop] = last[next][1-hop];
            }
        }
    } else {  // pos -= a[pos]
        int next = pos - a[pos];
        if (next <= 0) {
            yval[pos][hop] = a[pos];
            last[pos][hop] = pos;
            return;
        } else {
            if (!vis[next][1-hop]) dfs(next, 1-hop);
            else {
                if (yval[next][1-hop] == 0)
                    yval[next][1-hop] = LOOP;
            }
            long long prev = yval[next][1-hop];
            if (prev == LOOP) {
                yval[pos][hop] = LOOP;
            } else {
                yval[pos][hop] = yval[next][1-hop] + a[pos];
                last[pos][hop] = last[next][1-hop];
            }
            return;
        }
    }
}

int main()
{
    cin >> n;
    for (int i=2; i<=n; ++i) cin >> a[i];
    a[1] = 1;
    for (int pos=2; pos<=n; ++pos)
    for (int hop=0; hop<=1; ++hop)
    if (!vis[pos][hop]) {
        dfs(pos, hop);
    }
    for (a[1]=1; a[1]<n; ++a[1]) {
        int x = 1+a[1];
        int offset = a[1];
        long long ans = yval[x][1];
        if (ans == LOOP) cout << -1 << endl;
        else {
            if (last[x][1] == 1) offset += a[1]-1;
            cout << ans + offset << endl;
        }
    }
}

// Accepted
