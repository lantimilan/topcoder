// CHQUEENS.cc
#include <iostream>
using namespace std;

int N, M, X, Y;

int get_diag_for_piece(int r, int c, int cnt[]) {
    cnt[0] = min(r-1, c-1);
    cnt[1] = min(N-r, c-1);
    cnt[2] = min(N-r, M-c);
    cnt[3] = min(r-1, M-c);
}

void print(int a[], int size) {
    for (int i = 0; i < size; ++i) cout << ' ' << a[i];
    cout << endl;
}

int get_diag(int r, int c) {
    // -1, -1, (1,1)
    // +1, -1, (N,1)
    // +1, +1, (N,M)
    // -1, +1, (1,M)
    int queen[4], chef[4];
    get_diag_for_piece(r, c, queen); // cout << "queen:"; print(queen, 4);
    get_diag_for_piece(X, Y, chef);
    int cnt = 0;
    if (abs(X-r) == abs(Y-c)) {
        if (X < r && Y < c) {
            cnt = chef[0];
        } else if (X > r && Y < c) {
            cnt = chef[1];
        } else if (X > r && Y > c) {
            cnt = chef[2];
        } else {
            cnt = chef[3];
        }
        ++cnt;  // chef self
    }
    int ans = 0;
    for (int i = 0; i < 4; ++i) ans += queen[i];
    return ans - cnt;
}

// same row cells blocked by chef (X,Y)
int get_same_row(int r, int c) {
    if (r != X) return 0;
    int ans;
    if (c < Y) ans = (M-Y+1);
    else ans = Y;
    return ans;
}

int get_same_col(int r, int c) {
    if (c != Y) return 0;
    int ans;
    if (r < X) ans = (N-X+1);
    else ans = X;
    return ans;
}

void solve() {
    cin >> N >> M >> X >> Y;
    int ans = 0;
    for (int r1 = 1; r1 <= N; ++r1)
    for (int c1 = 1; c1 <= M; ++c1) {
        if (r1 == X && c1 == Y) continue;
        // chef at (X, Y)
        // same row, M-1
        // same col, N-1
        // same diag,
        int same_row = N-1 - get_same_row(r1, c1);
        int same_col = M-1 - get_same_col(r1, c1);
        int diag = get_diag(r1, c1);
//        cout << "r,c,same_row,same_col,diag "
//            << '(' << r1 << ',' << c1 << ')' << " "
//            << same_row
//            << ' ' << same_col
//            << ' ' << diag << endl;
        int bad = same_row + same_col + diag;
        ans += N * M - 2 - bad;  // 1 for self and 1 for chef
    }
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
