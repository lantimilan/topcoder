#include <string>
using namespace std;

class EllysNewNickname
{
public:

bool is_vowel(char ch)
{
	char vowels[] = "aeiouy";
	int len = strlen(vowels);
	for (int i = 0; i < len; ++i)
		if (ch == vowels[i]) return true;
	return false;
}

int getLength(string nickname)
{
	int n = nickname.size();
	int ans = n;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (is_vowel(nickname[i])) cnt++;
		else {
			if (cnt > 0) ans -= cnt-1;
			cnt = 0;
		}
	}
	if (cnt > 0) ans -= cnt-1;
	return ans;
}

};
