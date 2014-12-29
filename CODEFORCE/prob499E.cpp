// prob499E.cpp
// maximum matching
// The key is: good pairs (i,j) has i+j being odd
// build graph
// vertex, for each elemnt a[i] and its prime factor p,
// make a vertex v = (a[i], p)
// for each pair (i,j) and some prime p
// connect (a[i],p) with (a[j],p), this means we divide a[i] and a[j] by p
// if p occurs r times, add r vertices of the form (a[i], p)
// then it is a maximum matching of bipartite graph

#include <iostream>
using namespace std;

int main()
{
    int n, m; cin >> n >> m;
    int a[105];
    for (int i = 0; i < n; ++i) cin >> a[i];
    int first[105], second[105];
    for (int i = 0; i < m; ++i) {
        cin >> first[i] >> second[i];
    }
}
