#include <cstring>
using namespace std;

class TorusSailing
{
public:

// Gauss Seidel method
double expectedTime(int N, int M, int goalX, int goalY)
{
	double expect[105][105];
	memset(expect, 0, sizeof expect);
	for (int round = 0; round < 10000; ++round) {
		for (int x = 0; x < N; ++x)
		for (int y = 0; y < M; ++y)
		{
			if (x==0 && y==0) continue;
			int x1 = (x-1) % N; if (x1 < 0) x1 += N;
			int y1 = y;
			int x2 = x;
			int y2 = (y-1) % M; if (y2 < 0) y2 += M;
			expect[x][y] = 1 + 0.5 * (expect[x1][y1] + expect[x2][y2]);
		}
	}
	return expect[goalX][goalY];
}
};
