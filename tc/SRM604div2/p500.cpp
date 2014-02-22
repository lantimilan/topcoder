#include <string>
#include <iostream>
using namespace std;

class PowerOfThreeEasy
{
public:
// represent by 3-ary
// possible iff two directions have no overlap

bool getMask(int x, int &mask)
{
	mask = 0;
	int p = 0;
	while (x) {
		int d = x % 3; x /= 3;
		if (d == 2) return false;
		mask |= d << p;
		p++;
	}
	return true;
}

string ableToGet(int x, int y)
{
	const string good = "Possible";
	const string bad = "Impossible";
	if (x == 0 && y == 0) return good;	
	int maskX = 0, maskY = 0;
	if (!getMask(x, maskX)) return bad;
	if (!getMask(y, maskY)) return bad;
	cout << maskX << ' ' << maskY << endl;
	if ((maskX & maskY) == 0) {
		int t = maskX | maskY;
		if ((t & (t+1)) == 0) return good;
	}
	return bad;
}
};
