#include <string>
using namespace std;

class OneDimensionalRobotEasy
{
public:

int finalPosition(string commands, int A, int B)
{
	int pos = 0;
	for (int i = 0; i < commands.size(); ++i) {
		if (commands[i] == 'L') pos--;
		else pos++;
		if (pos < -A) pos = -A;
		if (pos > B) pos = B;
	}
	return pos;
}
};
