// only 3 choices
// empty
// single edge
// length 2 path
// star
//
// update: build adj matrix helps find triangle
// Gassa has almost the same code, why I cannot pass the last sample testcase?
#include <algorithm>
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
    int a[3];
    for (a[0]=1; a[0]<=n; ++a[0])
    for (a[1]=a[0]+1; a[1]<=n; ++a[1])
    for (a[2]=a[1]+1; a[2]<=n; ++a[2])
    {
        bool edge[3] = {0};
        for (int x=0; x<3; ++x) {
            int b1 = a[x], b2 = a[(x+1)%3];
            for (int i=0; i<m; ++i)
                if (p1[i] == b1 && p2[i] == b2
                	|| p1[i] == b2 && p2[i] == b1) edge[x] = 1;
        }
        ans += edge[0] && edge[1] && edge[2];
    }

    return ans;
}
};
