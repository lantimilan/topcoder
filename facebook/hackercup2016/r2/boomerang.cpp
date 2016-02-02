// boomerang.cpp
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int M = 1e5;
int myleft[M+5];
int myright[M+5];
int leftcover[M+5];
int rightcover[M+5];
int N;
string s1, s2;

void reach_from_left(const string &str, const string &target) {
    char prev = '*';
    int ndist = 0;
    int cost = 0;
    myleft[0] = 0;
    for (int i = 0, j = 1; i < N; ++i, ++j) {
        char ch = target[i];
        if (ch != prev) {
            ndist++;
            prev = ch;
        }
        if (ch != str[i]) {
            cost = ndist;
        }
        myleft[j] = cost;
    }
}

void reach_from_right(const string &str, const string &target) {
    char prev = '*';
    int ndist = 0;
    int cost = 0;
    myright[0] = 0;
    for (int i = N-1, j = 1; i >= 0; --i, ++j) {
        char ch = target[i];
        if (ch != prev) {
            ndist++;
            prev = ch;
        }
        if (ch != str[i]) {
            cost = ndist;
        }
        myright[j] = cost;
    }
}

void chmax(int &a, int b) {
    if (a < b) a = b;
}

void solve(int tcase) {
    cin >> N >> s1 >> s2;
    reach_from_left(s1, s2);
    reach_from_right(s1, s2);

//    for (int i = 0; i <= N; ++i) cout << myleft[i] << ' '; cout << endl;
//    for (int i = 0; i <= N; ++i) cout << myright[i] << ' '; cout << endl;

    memset(leftcover, 0, sizeof leftcover);
    memset(rightcover, 0, sizeof rightcover);
    int maxcost = 0;
    for (int i = 0; i <= N; ++i) {
        int cost = myleft[i];
        chmax(maxcost, cost);
        chmax(leftcover[cost], i);
    }
    for (int i = 0; i <= N; ++i) {
        int cost = myright[i];
        chmax(maxcost, cost);
        chmax(rightcover[cost], i);
    }

    for (int c = 1; c <= maxcost; ++c) {
        chmax(leftcover[c], leftcover[c-1]);
        chmax(rightcover[c], rightcover[c-1]);
    }

//    for (int i = 0; i <= maxcost; ++i) cout << leftcover[i] << ' '; cout << endl;
//    for (int i = 0; i <= maxcost; ++i) cout << rightcover[i] << ' '; cout << endl;

    int best;
    for (best = maxcost; best >= 0; --best) {
        if (leftcover[best] + rightcover[best] < N) break;
    }

    // output
    cout << "Case #" << tcase << ": ";
    cout << best+1 << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
