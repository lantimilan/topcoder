// prob406A.cpp
//
// work out 3x3 matrix for the unusual product
// under GL2, only a11^2 + a22^2 + a33^2 matters, other entries show up twice
// and would be 0 under GF2 regardless of its value being zero or one


#include <cstdio>
using namespace std;

int mat[1005][1005];

int main()
{
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
        scanf("%d", &mat[i][j]);

    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum ^= mat[i][i];

    int q; scanf("%d", &q);
    while (q--) {
        int op; scanf("%d", &op);
        int x;
        if (op == 1 || op == 2) {
            scanf("%d", &x);
            sum = 1 - sum;
        } else {
            printf("%d", sum);
        }
    }
}
