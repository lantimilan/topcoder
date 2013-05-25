#include <algorithm>
#include <vector>
using namespace std;

// count R,G,B
// sort reverse
//
// if three color, try each pair and the third one is in a max box

class BallsSeparating
{
public:
int minOperations(vector <int> red, vector <int> green, vector <int> blue)
{
	int N = red.size();
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += red[i] + green[i] + blue[i];
	}
	if (N < 3) return -1;
	int best = sum;
	for (int r = 0; r < N; ++r)
	for (int g = 0; g < N; ++g) if (g != r)
	for (int b = 0; b < N; ++b) if (b != r && b != g)
	{
	int curr = 0;
	for (int i = 0; i < N; ++i)
	{
		if (i == r) { curr += green[i] + blue[i]; continue; }
		if (i == g) { curr += red[i] + blue[i]; continue; }
		if (i == b) { curr += red[i] + green[i]; continue; }
		int x, y, z;
		x = red[i], y = green[i], z = blue[i];
		curr += x + y + z - max(x, max(y,z));
	}
	best = min(best, curr);
	}
	return best;
}
};
