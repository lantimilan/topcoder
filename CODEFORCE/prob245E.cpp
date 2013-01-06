// use the first one to kill + - until end
// O(n^2)

#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
    string seq; cin >> seq;
    int ans = 0;

    int i, j;
    for (i=0; i<seq.size(); ++i) {
        for (j=0; j<seq.size(); ++j)
            if (seq[j] != 'X') break;
        if (j>=seq.size()) break;
        char ch = seq[j];
        seq[j] = 'X';
        for (++j; j<seq.size(); ++j)
            if (seq[j] == 'X') {}
            else if (ch != seq[j]) { ch = seq[j]; seq[j] = 'X'; }

        ans++;
    }
    for (i=0; i<seq.size(); ++i)
        ans += (seq[i] != 'X');
    cout << ans << endl;
}
