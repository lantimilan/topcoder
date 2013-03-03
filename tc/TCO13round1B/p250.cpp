#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class EllysPairs
{
public:
int getDifference(vector <int> know)
{
	sort(know.begin(), know.end());
	int a = 0, b = 100 * 1000;
	int n = know.size();
	for (int i=0; i<n/2; ++i) {
		int cur = know[i] + know[n-1-i];
		a = max(a, cur);
		b = min(b, cur);
		//cout << a << ' ' << b << endl;
	}
	return a - b;
}
};
