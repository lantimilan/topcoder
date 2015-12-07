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
    if (pos-1 >= 0 && (get_bit(conf,pos-1) & 2)) return true;
    if (pos+1 < M && (get_bit(conf,pos+1) & 1)) return true;
    return false;
}

int update(int conf, int pos, int row) {
    int newconf = 0;
    for (int j = 0; j < M; ++j) {
        int val = get_bit(conf, j);
        if (j-1 >= 0 && (val & 1)) set_bit(newconf, j-1, 1);
        if (j+1 < M && (val & 2)) set_bit(newconf, j+1, 2);
    }
    for (int j = 0; j < M; ++j) if (is_obstacle(board[row][j])) {
        clear_bit(newconf, j);
    }
    set_bit(newconf, pos, 3);
    return newconf;
}

int main() {
    cin >> N >> M;
    board.resize(N);
    for (int i = 0; i < N; ++i) cin >> board[i];

    for (int j = 0; j < M; ++j) if (!is_obstacle(board[0][j])) {
        int conf = 0; set_bit(conf, j, 3);
        dp[0][conf] = 1;
    }
    for (int i = 1; i < N; ++i)
    for (int j = 0; j < M; ++j) if (!is_obstacle(board[i][j])) {
        for (int conf = 0; conf < (1<<2*M); ++conf) if (!is_attack(conf, j)) {
            int newconf = update(conf, j, i);
            dp[i][newconf] += dp[i-1][conf];
        }
    }
    int ans = 0;
    for (int c = 0; c < (1<<2*M); ++c) ans += dp[N-1][c];
    cout << ans << endl;
}
