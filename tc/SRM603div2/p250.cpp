#include <string>
using namespace std;

class MiddleCode
{
public:

string encode(string s)
{
	string t = "";
	while (!s.empty()) {
		int n = s.length();
		if (n & 1) {
			char ch = s[n/2];
			s = s.substr(0, n/2) + s.substr(n/2 + 1);
			t += ch;
		} else {
			char c1, c2;
			c1 = s[n/2 - 1]; c2 = s[n/2];
			if (c1 < c2) {  // delete c1
				s = s.substr(0, n/2-1) + s.substr(n/2);
				t += c1;
			} else {
				s = s.substr(0, n/2) + s.substr(n/2 + 1);
				t += c2;
			}
		}
	}
	return t;
}
};
