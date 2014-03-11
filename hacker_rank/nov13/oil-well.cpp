// oil-well.cpp
//
// coordinate transformation:
// (x, y) -> (u, v)
// such that u = (x + y) / 2 and v = (x - y) / 2
// then Linf distance of (x, y) is L1 distance of (u, v)
// so the problem becomes 1 dimensional as each dim is independent now
//
// no, you still need to figure out a permutation of all cells

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int, int> pii;  // pos, cnt
int R, C;
int M[55][55];

int main()
{
    cin >> R >> C;
    for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c)
        cin >> M[r][c];

    int Rcnt[55]; memset(Rcnt, 0, sizeof Rcnt);
    int Ccnt[55]; memset(Ccnt, 0, sizeof Ccnt);
    for (int r = 0; r < R; ++r)
    for (int c = 0; c < C; ++c) {
        Rcnt[r] += M[r][c];
        Ccnt[c] += M[r][c];
    }

}

