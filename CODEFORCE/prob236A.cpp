#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s; cin >> s;
	int cnt[30] = {0};
	for(int i=0; i<s.size(); ++i)
		cnt[s[i]-'a'] = 1;
	int sum = 0;
	for(int i=0; i<26; ++i)
		sum += cnt[i];

	if (sum & 1) { // male
		cout << "IGNORE HIM!" << endl;
	} else { // female
		cout << "CHAT WITH HER!" << endl;
	}
}

