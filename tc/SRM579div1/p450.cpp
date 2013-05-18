#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
using namespace std;


int dp[1<<16][55];
int dist[55][55];
int edge[55][55];
int OPEN[55];
int CLOSE[55];
int DURATION[55];
const int INF = 500000000;

class TravellingPurchasingMan
{
public:

void shortest(int N)
{
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
		dist[i][j] = edge[i][j];

	for (int k = 0; k < N; ++k)		
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
		dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
}

int maxStores(int N, vector <string> interestingStores, vector <string> roads)
{
	// parse store
	int M = interestingStores.size();
	for (int i = 0; i < M; ++i) {
		istringstream iss(interestingStores[i]);
		iss >> OPEN[i] >> CLOSE[i] >> DURATION[i];
	}
	// parse edge
	for (int i = 0; i < N; ++i)
	for (int j = 0; j < N; ++j)
		edge[i][j] = INF;
	for (int i = 0; i < N; ++i)
		edge[i][i] = 0;
	for (int i = 0; i < roads.size(); ++i) {
		istringstream iss(roads[i]);
		int a, b, len;
		iss >> a >> b >> len;
		edge[a][b] = edge[b][a] = len;
	}
	
	// shortest path
	shortest(N);

	// dp[mask][last], min time to visit all mask stores and end at last
	memset(dp, -1, sizeof dp);
	dp[0][N-1] = 0;
	for (int mask = 0; mask < (1<<M); ++mask)
	for (int last = 0; last < N; ++last) if (dp[mask][last] >= 0) {
		//cout << "mask " << mask << ' ' << last << ' ' << dp[mask][last] << endl;
		int depart = dp[mask][last];

		for (int next = 0; next < M; ++next) {
			int arrival = depart + dist[last][next];
			if (arrival > CLOSE[next]) continue;
			int finish = max(arrival, OPEN[next]) + DURATION[next];
			int &entry = dp[mask | 1<<next][next];
			if (entry < 0 || entry > finish) entry = finish;
		}
	}
	//cout << "done\n";
	int ans = 0;
	for (int i = 0; i < M; ++i)
	for (int mask = 0; mask < (1<<M); ++mask) if (dp[mask][i] >= 0)
	{
		int cnt = 0;
		for (int p = 0; p < M; ++p) if (mask & 1<<p) cnt++;
		ans = max(ans, cnt);
		//cout << i << ' ' << mask << ' ' << cnt << ' ' << ans << endl;
	}
	return ans;
}
};
