#include <vector>
#include <string>
using namespace std;

// need two 1 and one 0
// 0 1 will tell and from or
// 1 1 will tell or from xor
class TheDeviceDiv2
{
public:
string identify(vector <string> plates)
{
	bool good = true;
	for (int p = 0; p < plates[0].size(); ++p) {
		int cnt[2] = {0};
		for (int i = 0; i < plates.size(); ++i) {
			char ch = plates[i][p];
			cnt[ch - '0']++;
		}
		if (cnt[0] >= 1 && cnt[1] >= 2) {}
		else { good = false; break; }
	}
	if (good) return "YES";
	else return "NO";
}
};
