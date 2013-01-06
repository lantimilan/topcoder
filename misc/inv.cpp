// computes the inverse of a to p
#include <cassert>
#include <cstdio>
using namespace std;

int inv(int a, int p)
{
    if (a==1) return 1;
    int q, r, k, b, v;
    q = p/a, r = p%a;  // p = q*a + r
    b = inv(r, a);  // b*r - k*a = 1
    k = (b*r-1)/a;
    v = (-(b*q + k)) % p;  // g++, modulo operator only give abs(res) < p
    return (v+p) % p;
}

int main()
{
    int p = 1019;
    for (int i=1; i<p; ++i) {
        int v = inv(i,p);
        //printf("%d * %d = %d\n", i, v, i*v);
        assert(i * v % p == 1);
    }
}
