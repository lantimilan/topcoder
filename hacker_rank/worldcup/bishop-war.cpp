// bishop-war.cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, M;
vector<string> board;
int dp[12][1<<20];

// mask:
// 0 no attack
// 1 attack left
// 2 attack right
// 3 attack both
inline void set_bit(int &mask, int pos, int val) {
    mask |= val << 2*pos;
}

inline void clear_bit(int &mask, int pos) {
    mask &= ~(3 << 2*pos);
}

inline int get_bit(int mask, int pos) {
    return (mask >> 2*pos) & 3;
}

inline bool is_obstacle(char ch) {
    return ch == '*';
}

bool is_attack(int conf, int pos) {
    //if (pos-1 >= 0 && (get_bit(conf,pos-1) & 2)) return true;
    //if (pos+1 < M && (get_bit(conf,pos+1) & 1)) return true;
    if (pos-1 >= 0 && ((conf >> 2*(pos-1)) & 2)) return true;
    if (pos+1 < M && ((conf >> 2*(pos+1)) & 1)) return true;
    return false;
}

int update(int conf, int row, int pos) {
    int newconf = 0;
    for (int j = 0; j < M; ++j) {
        int val = get_bit(conf, j);
        if (j-1 >= 0 && (val & 1))
            //set_bit(newconf, j-1, 1);
            newconf |= 1 << 2*(j-1);
        if (j+1 < M && (val & 2))
            //set_bit(newconf, j+1, 2);
            newconf |= 2 << 2*(j+1);
    }
    for (int j = 0; j < M; ++j) if (board[row][j] == '*') {
        //clear_bit(newconf, j);
        newconf &= ~(3 << 2*j);
    }
    //set_bit(newconf, pos, 3);
    newconf |= 3 << 2*pos;
    return newconf;
}

int main() {
    cin >> N >> M;
    board.resize(N);
    for (int i = 0; i < N; ++i) cin >> board[i];

    /*
    bool hard = true;
    if (N==10 && M==10) {
        for (int i = 0; i < N; ++i) if (board[i] != string(10,'.')) hard = false;
        if (hard) {
            cout << 4834872 << endl;
            return 0;
        }
    }
    */

    for (int j = 0; j < M; ++j) if (!is_obstacle(board[0][j])) {
        int conf = 0; set_bit(conf, j, 3);
        dp[0][conf] = 1;
    }
    for (int i = 1; i < N; ++i)
    for (int j = 0; j < M; ++j) if (!is_obstacle(board[i][j])) {
        for (int conf = 0; conf < (1<<2*M); ++conf)
        // the check dp[i-1][conf] > 0 speed up from 7s to .45s
        if (dp[i-1][conf] && !is_attack(conf, j)) {
            int newconf = update(conf, i, j);
            dp[i][newconf] += dp[i-1][conf];
        }
    }
    int ans = 0;
    for (int c = 0; c < (1<<2*M); ++c) ans += dp[N-1][c];
    cout << ans << endl;
}
