// more-multiplication.cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> get_digits(int k) {
    vector<int> digits;
    do {
        digits.push_back(k % 10);
        k /= 10;
    } while (k);
    return digits;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        vector<int> nds, mds;
        nds = get_digits(n);
        mds = get_digits(m);

        int nd = nds.size();
        int md = mds.size();
        int w, h;
        w = nd * 4 + 1 + 4;
        h = 2 + 2 + md*4 + 1;

        vector<string> table(h, string(w, ' '));
        table[0][0] = table[0][w-1] = table[h-1][0] = table[h-1][w-1] = '+';
        for (int i = 1; i < w-1; ++i) table[0][i] = table[h-1][i] = '-';

        for (int i = 1; i < h-1; ++i) table[i][0] = table[i][w-1] = '|';

        for (int i = 2; i < h-2; i += 4) {
            for (int j = 2; j < w-2; j ++) {
                table[i][j] = ((j-2) % 4) ? '-' : '+';
            }
        }
        for (int j = 2; j < w-2; j += 4)
        for (int i = 2; i < h-2; ++i) {
            if ((i-2) % 4) table[i][j] = '|';
        }

        int row, col;
        row = 1;
        for (int j = 0; j < nd; ++j) {
            table[row][4 + 4*j] = nds[nd-1-j] + '0';
        }
        col = w-2;
        for (int i = 0; i < md; ++i) {
            table[4 + i*4][col] = mds[md-1-i] + '0';
        }

        for (int i = 0; i < md; ++i)
        for (int j = 0; j < nd; ++j) {
            int p = mds[md-1-i] * nds[nd-1-j];
            int d1 = p / 10;
            int d2 = p % 10;

            int r = 4 + 4 * i;
            int c = 4 + 4 * j;
            table[r-1][c-1] = d1 + '0';
            table[r+1][c+1] = d2 + '0';
        }

        // print slash
        for (int i = md-1; i >= 0; --i) {
            int r = 4 + 4 * i;
            int c = w-2;
            --r; c -= 2;
            while (r < h-1 && c > 0) {
                if (table[r][c] == ' ') table[r][c] = '/';
                ++r; --c;
            }
        }
        for (int j = nd-1; j >= 0; --j) {
            int r = 1;
            int c = 4 + 4 * j;
            r += 2; ++c;
            while (r < h-1 && c > 0) {
                if (table[r][c] == ' ') table[r][c] = '/';
                ++r; --c;
            }
        }

        // add diagonal digits
        int carry = 0;
        for (int i = md-1; i >= 0; --i) {
            int d = carry;
            int r = 4 + 4 * i;
            int c = w-2;
            ++r; c -= 2;
            while (r+2 < h-1 && c-2 > 0) {
                d += table[r][c] - '0';
                r += 2;
                c -= 2;
            }
            carry = d / 10;
            d %= 10;
            table[r][c] = d + '0';
        }

        for (int j = nd-1; j >= 0; --j) {
            int d = carry;
            int r = 1;
            int c = 4 + 4 * j;
            r += 2; c--;
            while (r+2 < h-1 && c-2 > 0) {
                d += table[r][c] - '0';
                r += 2; c -= 2;
            }
            carry = d / 10;
            d %= 10;
            table[r][c] = d + '0';

            row = r; col = c;
        }

        // erase leading zero and its slash
        if (table[row][col] == '0') {
            table[row][col] = ' ';
            table[row+2][col] = ' ';
        }

        ///////////////////////////////////////////////
        for (int i = 0; i < h; ++i) {
            cout << table[i] << endl;
        }
    }
}
