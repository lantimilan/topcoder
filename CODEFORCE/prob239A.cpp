#include <cstdio>
using namespace std;

int main()
{
    int y, k, n; scanf("%d%d%d", &y, &k, &n);

    bool found = false;
    int lim = n/k;
    for (int i=1; i<=lim; ++i) {
        int x = i*k - y;
        if (x > 0) {
            if (found) putchar(' ');
            printf("%d", x);
            found = true;
        }
    }
    if (!found) printf("-1");
    putchar('\n');
}
