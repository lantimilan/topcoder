#include <vector>
using namespace std;

class RobotHerbDiv2
{
public:

int getdist(int T, vector <int> a)
{
	int dir = 0;
	int dist[4] = {0};
	for (int t = 0; t < T; ++t) {
		for (int i = 0; i < a.size(); ++i) {
			dist[dir] += a[i];
			dir = (dir + a[i]) % 4;
		} 
	}
	int ans = abs(dist[0] - dist[2]) + abs(dist[1] - dist[3]);
	return ans;
}

};
