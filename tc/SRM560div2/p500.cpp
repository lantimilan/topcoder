#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

class TomekPhone {
public:
int minKeystrokes(vector <int> freq, vector <int> keySizes)
{
	int sum = 0;
	for (int i=0; i<keySizes.size(); ++i)
		sum += keySizes[i];
	if (sum < freq.size()) return -1;
	sort(freq.begin(), freq.end(), greater<int>());
	vector<int> idx(keySizes.size(), 0);
	int ans = 0;
	for (int i=0; i<freq.size(); ++i) {
		int mink = -1;
		int j;
		for (j=0; j<keySizes.size(); ++j) {
			if (idx[j] < keySizes[j]) {
				if (mink < 0 || idx[mink] > idx[j])
					mink = j;
			}
		}
		ans += freq[i] * (idx[mink]+1);
		idx[mink]++;
	}
	return ans;
}
};
// greedy