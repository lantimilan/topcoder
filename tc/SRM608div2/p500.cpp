#include <algorithm>
#include <vector>
using namespace std;

class MysticAndCandiesEasy
{
public:

int minBoxes(int C, int X, vector <int> high)
{
	sort(high.begin(), high.end());
	int num = high.size();
	int candies = C;
	int p = 0;
	while (candies >= X) {
		candies -= high[p];
		p++;
		num--;
	}
	return num+1;
}
};
