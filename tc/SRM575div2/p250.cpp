#include <vector>
using namespace std;

// first can assume the sequence is sorted
//
// if a[i] == a[j], then swap results in the same sequence
// else they are different
//
// ans = sum of s[i] * s[j] + (some s[i] > 1)
// s[i] is count of value

class TheSwapsDivTwo
{
public:
int find(vector <int> sequence)
{
	int value[50] = {0};
	for (int i = 0; i < sequence.size(); ++i)
		value[sequence[i]]++;
	int cnt = 0;
	for (int i = 1; i < 50; ++i) cnt = max(cnt, value[i]);
	
	int ans = 0;
	for (int i = 1; i < 50; ++i)
	for (int j = i+1; j < 50; ++j)
		ans += value[i] * value[j];
	ans += (cnt > 1);
	return ans;
}
};
