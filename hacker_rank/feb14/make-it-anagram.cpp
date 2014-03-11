// make-it-anagram,cpp
//
// anagram depends on count of char
//
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

string A, B;

int cnt[2][30];

int main()
{
    getline(cin, A);
    getline(cin, B);

    for (int i = 0; i < A.length(); ++i) cnt[0][A[i]-'a']++;
    for (int i = 0; i < B.length(); ++i) cnt[1][B[i]-'a']++;

    int ans = 0;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        int x = ch - 'a';
        ans += abs(cnt[0][x] - cnt[1][x]);
    }

    cout << ans << endl;
}
