#include <string>
#include <vector>
using namespace std;

string S;

class PalindromicSubstringsDiv2
{
public:
// for each center, grow to both ends
// O(n^2)
int count(vector <string> S1, vector <string> S2)
{
	for (int i = 0; i < S1.size(); ++i) S += S1[i];
	for (int i = 0; i < S2.size(); ++i) S += S2[i];
	
	int ans = 0;
	int n = S.size();
	for (int c = 0; c < 2*n+1; ++c) {
		int len = 0;
		int p1, p2;
		if (c & 1) { len++; p1 = c/2 - 1; p2 = p1 + 2; }
		else { p1 = c/2 - 1; p2 = p1 + 1; }
		while (0 <= p1 && p2 < n && S[p1] == S[p2]) {
			len++; p1--; p2++;
		}
		ans += len;
	}
	return ans;
}
};
