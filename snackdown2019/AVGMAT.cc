#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> house_map;

bool is_house(int r, int c, int nrow, int ncol) {
    return 0 <= r && r < nrow && 0 <= c && c < ncol && house_map[r][c] == '1';
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        house_map.resize(N);
        for (int i = 0; i < N; ++i) cin >> house_map[i];

        vector<int> counts(N + M - 2 + 1);
        for (int dist = 1; dist <= N + M - 2; ++dist) {
        int ans = 0;
        for (int r = 0; r < N; ++r)
        for (int c = 0; c < M; ++c) if (house_map[r][c] == '1') {
            // rowdiff = 0
            if (is_house(r + dist, c, N, M)) ans++;
            if (is_house(r - dist, c, N, M)) ans++;
            // coldiff = 0
            if (is_house(r, c + dist, N, M)) ans++;
            if (is_house(r, c - dist, N, M)) ans++;
            for (int rowdiff = 1; rowdiff < dist; ++rowdiff) {
                int coldiff = dist - rowdiff;
                const int dir[][2] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};
                for (int x = 0; x < 4; ++x) {
                    int r2 = r + rowdiff * dir[x][0];
                    int c2 = c + coldiff * dir[x][1];
                    if (is_house(r2, c2, N, M)) {
                        ans++;
                    }
                }
            }
        }
        assert(ans % 2 == 0);
        counts[dist] = ans / 2;
        }
        for (int d = 1; d <= N+M-2; ++d) {
            if (d > 1) cout << ' ';
            cout << counts[d];
        }
        cout << endl;
    }
}
