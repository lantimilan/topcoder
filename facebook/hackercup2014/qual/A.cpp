// A.cpp
// square_detector_example_input.txt
// square_detector_example_output.txt
// T = 20
// N = 20
//
// dot is white and # is black
// YES if all black cells form a square

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isBlack(char ch)
{
    return ch == '#';
}

void solve(int tcase)
{
    int N; cin >> N;
    vector<string> board(N);
    for (int i = 0; i < N; ++i) {
        cin >> board[i];
    }
    int r1, c1, r2, c2;
    for (r1 = 0; r1 < N; ++r1)
    for (c1 = 0; c1 < N; ++c1)
    if (isBlack(board[r1][c1]))
        goto topleft;
topleft:
    for (r2 = N-1; r2 >= 0; --r2)
    for (c2 = N-1; c2 >= 0; --c2)
    if (isBlack(board[r2][c2]))
        goto bottomright;
bottomright:
    //cerr << r1 << ' ' << c1 << ' ' << r2 << ' ' << c2 << endl;
    bool ans = true;
    if (r2 - r1 != c2 - c1) {
        ans = false;
    }
    if (ans) {
        for (int r = r1; r <= r2; ++r)
        for (int c = c1; c <= c2; ++c)
            if (!isBlack(board[r][c]))
                ans = false;
    }
    cout << "Case #" << (tcase+1) << ": ";
    cout << (ans ? "YES" : "NO") << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 0; t < T; ++t)
        solve(t);
}
