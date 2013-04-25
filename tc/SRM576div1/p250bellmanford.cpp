// Bellman-Ford shortest path
// d[v] = min_(edge u,v) max(d[u], w(u,v))

#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

class ArcadeManao
{
public:

int shortestLadder(vector <string> level, int coinRow, int coinColumn)
{
	const int INF = 100;
	int d[60][60];
	int n = level.size();
	int m = level[0].size();
	
	for (int i = 0; i < n; ++i)
	for (int j = 0; j < m; ++j)
		d[i][j] = INF;
	
	d[n-1][0] = 0;
	
	bool update = true;
	while (update) {
		update = false;
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			for (int k = j-1; k >= 0 && level[i][k] == 'X'; --k) {
				if (d[i][k] > d[i][j]) {
					d[i][k] = d[i][j]; update = true;
				}
			}
			for (int k = j+1; k < m && level[i][k] == 'X'; ++k) {
				if (d[i][k] > d[i][j]) {
					d[i][k] = d[i][j]; update = true;
				}
			}
			for (int r = 0; r < n; ++r) if (level[r][j] == 'X') {
				int dnew = max(d[i][j], abs(i-r));
				if (d[r][j] > dnew) {
					d[r][j] = dnew; update = true;				
				}				
			}
		}
	}
	return d[coinRow-1][coinColumn-1];
}
};
