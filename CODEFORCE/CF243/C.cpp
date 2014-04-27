// C.cpp
//
// Notice that energy is large, energy e >= 10^3 and s is at most 3*10^5
// so we can get no more than 3*10^5 / 10^3 = 300 dollars
//
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


int a[100000+5];
int b[100000+5];
int match[100000+5];

int main()
{
    int n, m, start, energy; scanf("%d%d%d%d", &n, &m, &start, &energy);
    for (int i = 0; i < n; ++i) scanf("%d", a+i);
    for (int i = 0; i < m; ++i) scanf("%d", b+i);

    for (int i = n-1; i >= 0; --i) {
        match[i] = -1;
        for (int j = m-1; j >= 0; --j) {
            if (a[i] == b[j]) {
                match[i] = j; break;
            }
        }
    }
}
