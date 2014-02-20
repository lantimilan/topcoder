#include <string>
#include <set>
using namespace std;

class AlienAndPassword
{
public:

int getNumber(string S)
{
	set<string> st;
	for (int i = 0; i < S.size(); ++i) {
		string t = S.substr(0,i);
		t += S.substr(i+1);
		st.insert(t);
	}
	return st.size();
}
};
