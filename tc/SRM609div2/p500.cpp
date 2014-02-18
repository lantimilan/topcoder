// strategy:
// first get group of 3 with same color
// then remain must be 0, 1, 2, of each color
// if what we have are distinct colors, then we are opt
// if what we have is 1 and 1, or 1 and 0, then we are opt
// the only case that is not definitive is 1 and 2,
// in this case we claim that we are still opt, that is
// it is not possible to pack into 3-ball group only
// proof: let the colors be labeled 0, 1, and 2
// then each group of three balls must have a sum of multiple of 3
// yet in the 1 and 2 case, we know the sum of all labels of input is not a multiple of 3
// so we must have one group of size 2 and one group of size 1
#include <algorithm>
using namespace std;

class PackingBallsDiv2
{
public:

int min3(int a, int b, int c)
{
	return min(a, min(b, c));
}

int minPacks(int R, int G, int B)
{
	int ans = 0;
	ans += R / 3; R %= 3;
	ans += G / 3; G %= 3;
	ans += B / 3; B %= 3;
	
	int distinct = min3(R, G, B); ans += distinct;
	R -= distinct; G -= distinct; B -= distinct;
	// now at least one of R, G, B is 0
	// the other two are 1 or 2
	int rem = R + G + B;
	if (rem == 4) ans += 2;
	else if (rem == 3) ans += 2;
	else if (rem == 2 || rem == 1) ans += 1;
	else ans += 0;
	
	return ans;
}
};
