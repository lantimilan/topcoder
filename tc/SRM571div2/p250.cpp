#include <vector>
#include <string>
using namespace std;

class CityMap
{
public:
// count and match
string getLegend(vector <string> cityMap, vector <int> POIs)
{
	int n = POIs.size();
	string ans(n, ' ');
	for (int i = 0; i < n; ++i) {
		int cnt = POIs[i];
		for (char ch = 'A'; ch <= 'Z'; ++ch) {
			int occ = 0;
			for (int i = 0; i < cityMap.size(); ++i)
			for (int j = 0; j < cityMap[i].length(); ++j)
				occ += (cityMap[i][j] == ch);
			if (cnt == occ) { ans[i] = ch; break; } 
		}
	}
	return ans;
}
};
