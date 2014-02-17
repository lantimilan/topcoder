#include <algorithm>
#include <vector>
using namespace std;

class BoundingBox
{
public:
// min(X), min(Y) to max(X), max(Y)
int smallestArea(vector <int> X, vector <int> Y)
{
	int xmin = *min_element(X.begin(), X.end());
	int ymin = *min_element(Y.begin(), Y.end());
	int xmax = *max_element(X.begin(), X.end());
	int ymax = *max_element(Y.begin(), Y.end());
	return (xmax - xmin) * (ymax - ymin);
}
};
