// manacher.cpp
//
// Manacher's algorithm
// O(n) time finds all palindrome substring

#include <iostream>
using namespace std;

void manacher(string s, int span[])
{
    int n = s.size();
    int c = 0;  // center
    span[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = 2*c - i;
        if (j < 0) span[i] = 0;
        else span[i] = min(c+span[c]-i, span[j]);
        int l = c - span[c];
        int l1 = j - span[j];
        if (l1 <= l) {
            int p = i + span[i];
            int q = i - span[i];
            while (0 <= q && p < n && s[p] == s[q]) {
                p++; q--;
            }
            span[i] = p - i - 1;
            c = i;
        }
    }
}

int main()
{
    string s = "abababaababasa";
    int span[7];
    manacher(s, span);
    for (int i = 0; i < 7; ++i) {
        cout << span[i] << ' ';
    }
    cout << endl;
}
