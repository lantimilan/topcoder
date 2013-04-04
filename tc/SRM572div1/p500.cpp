//500, the length n is only 9, but brute force cannot work as we have 10^9
//numbers to check, each need to go through 50 guesses. It appears that if n is
//smaller, say 4 or 5, then we can work out by brute force. How do we do that?
//
//Reading tourist and petr's solution, and the editorial, it finally makes sense.
//Let's consider one guess, we can cut a number with 9 digits to left with 4
//digits and right with 5 digits. Then we try all 0 to 99999 to count the number
//of bull. If left bull and right bull add up to the right bull, then the left
//guess and right guess makes a valid guess. Now we have a number of guesses.
//
//What happens if we try 0 to 9999 for left and 0 to 99999 for right. And we
//record the signature of each try on left in a map, a signature is essentially
//the bull for each guess in the input, a vector of int with 50 elements. And we
//also record the signature of each try on the right, put in a second map. Each
//map entry has the signature as key, and number of tries with the signature as
//value.
//
//Now we can iterate through the first map, for each entry, we can compute its
//complement key in the second map and look for matches.
//
//In the end, we can count how many valid numbers with bulls matching all the
//input guesses. And it is trivial to respond 0, 1 or 2 for the problem.

// from 0 to 9999, try left
// from 0 to 99999, try right
//
// map count of tries to key = bull
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

map< vector<int>, int > cnt_left, cnt_right, val_left, val_right;

class EllysBulls
{
public:

string getNumber(vector <string> guesses, vector <int> bulls)
{
    int len = guesses[0].size();
    int g = guesses.size();
    int lim, l1, l2;

    lim = 1; l1 = len / 2; l2 = len - l1;
    for (int i = 0; i < l1; ++i) lim *= 10; cout << lim << endl;
    for (int i = 0; i < lim; ++i) {
        vector<int> vec;
        for (int k = 0; k < g; ++k) {
            int val = i;
            int bull = 0;
            for (int p = l1-1; p >= 0; --p) {
                if (guesses[k][p] - '0' == val % 10) bull++;
                val /= 10;
            }
            vec.push_back(bull);
        }
        val_left[vec] = i;
        cnt_left[vec]++;
    }
    lim = 1;
    for (int i = 0; i < l2; ++i) lim *= 10; cout << lim << endl;
    for (int i = 0; i < lim; ++i) {
        vector<int> vec;
        for (int k = 0; k < g; ++k) {
            int val = i;
            int bull = 0;
            for (int p = l2-1; p >= 0; --p) {
                if (guesses[k][p+l1] - '0' == val % 10) bull++;
                val /= 10;
            }
            vec.push_back(bull);
        }
        val_right[vec] = i;
        cnt_right[vec]++;
    }

    // from right search left
    int ans_left = 0, ans_right = 0;
    int ans = 0;
    for (int i = 0; i < lim; ++i) {
        vector<int> vec, other;
        for (int k = 0; k < g; ++k) {
            int val = i;
            int bull = 0;
            for (int p = l2-1; p >= 0; --p) {
                if (guesses[k][p+l1] - '0' == val % 10) bull++;
                val /= 10;
            }
            vec.push_back(bull);
        }
        bool good = true;
        for (int k = 0; k < g; ++k) {
            int entry = bulls[k] - vec[k];
            if (entry < 0) { good = false; break; }
            other.push_back(entry);
        }
        if (!good) continue;
        if (cnt_left.count(other)) {
            ans_right = i; ans_left = val_left[other];
            ans += cnt_left[other] * cnt_right[vec];
            if (ans >= 2) break;
        }
    }
    if (ans == 0) return "Liar";
    if (ans >= 2) return "Ambiguity";
    string str;
    for (int p = 0; p < l2; ++p) {
        str += char(ans_right % 10 + '0');
        ans_right /= 10;
    }
    for (int p = 0; p < l1; ++p) {
        str += char(ans_left % 10 + '0');
        ans_left /= 10;
    }
    for (int p = 0, q = str.length()-1; p < q; ++p, --q) {
        char t = str[p]; str[p] = str[q]; str[q] = t;
    }
    return str;
}

};
