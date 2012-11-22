// notice |E| = 5000
//
// algorithm:
// for each node (at most 5000*2)
//   for each nb of node  // this loop runs in O(E) time
//     update step=2 cnt
//   among all nodes, find one with max cnt

#include <iostream>
#include <map>
#include <string>
using namespace std;

int N;  // N can be up to 10000 because 5000 edges
int adj[10000+5][5005];  // adj[i][x] = j means (i,j) is an edge
int cnt[10000+5];
int nbcnt[10000+5];
map<string, int> names;
string lookup[10000+5];

int main()
{
  int m; cin >> m;
  N = 0;
  for (int i=0; i<m; ++i) {
    string a, b; cin >> a >> b;
    int xa, xb;
    if (names.find(a) == names.end()) { lookup[N] = a; names[a] = N++; }
    if (names.find(b) == names.end()) { lookup[N] = b; names[b] = N++; }
    xa = names[a], xb = names[b];
    adj[xa][cnt[xa]++] = xb;
    adj[xb][cnt[xb]++] = xa;
  }

  cout << N << endl;
  for (int s=0; s<N; ++s) {
    for (int i=0; i<N; ++i) nbcnt[i] = 0;
    nbcnt[s] = -1;
    for (int x=0; x<cnt[s]; ++x) {
    	int nb = adj[s][x];
    	nbcnt[nb] = -1;
    }
    for (int x=0; x<cnt[s]; ++x) {
      int nb = adj[s][x];
      for (int y=0; y<cnt[nb]; ++y) {
        int hop = adj[nb][y];
	if (nbcnt[hop]>=0) nbcnt[hop]++;
      }
    }
    // if node a do not have any 2-hop path, then all other nodes
    // are its recommended friends
    int maxval = 0;
    for (int i=0; i<N; ++i) {
      //cout << lookup[s] << ' ' << lookup[i] << ' ' << nbcnt[i] << endl;
      maxval = max(maxval, nbcnt[i]);
    }
    int friendcnt = 0;
    for (int i=0; i<N; ++i)
      friendcnt += (nbcnt[i] == maxval);
    cout << lookup[s] << ' ' << friendcnt << endl;
  }
}
