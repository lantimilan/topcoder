#include <vector>
using namespace std;

class Chopsticks
{
public:

int getmax(vector <int> length)
{
	int cnt = 0;
	int avail[105] = {0};
	for (int i = 0; i < length.size(); ++i) avail[length[i]]++;
	for (int h = 1; h <= 100; ++h) cnt += avail[h]/2;
	return cnt;
}
};
