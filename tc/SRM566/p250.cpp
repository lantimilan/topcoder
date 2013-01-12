// only 3 choices
// empty
// single edge
// length 2 path
// star
//
// update: build adj matrix helps find triangle
// Gassa has almost the same code, why I cannot pass the last sample testcase?
#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

class PenguinSledding
{
public:
long long countDesigns(int n, vector <int> p1, vector <int> p2)
{
    int m = p1.size();
    long long ans = m+1;

    // star
    for (int c=1; c<=n; ++c)
    {
    int nb = 0;
    for (int i=0; i<m; ++i) if (p1[i] == c || p2[i] == c) nb++;
    ans += (1LL<<nb) - (1+nb);
    }
    // triangle
    int a[60][60]; memset(a, 0, sizeof a);
    for (int i=0; i<m; ++i) a[p1[i]][p2[i]] = a[p2[i]][p1[i]] = 1;
    for (int b1=1; b1<=n; ++b1)
    for (int b2=b1+1; b2<=n; ++b2)
    for (int b3=b2+1; b3<=n; ++b3)
        if (a[b1][b2] && a[b2][b3] && a[b3][b1])
            ans++;
    return ans;
}
};
