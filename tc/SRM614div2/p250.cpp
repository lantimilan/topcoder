#include <sstream>
#include <string>
using namespace std;

class MicroStrings
{
public:

string makeMicroString(int A, int D)
{
	ostringstream oss;
	int val = A;
	while (val >= 0) {
		oss << val;
		val -= D;
	}
	return oss.str();
}
};
