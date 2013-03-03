#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// try all possible 2^15 moves for rows
// then the moves for cols are determined
class EllysFigurines
{
public:
int getMoves(vector <string> board, int R, int C)
{
	int nrow = board.size(), ncol = board[0].size();
	int best = nrow;
	vector<string> tmp;
	for (int mask = 0; mask < (1<<nrow); ++mask) {
		tmp = board;
		int move = 0;
		for (int i = 0; i < nrow; ++i) if (1<<i & mask) {
			move++;
			for (int k = 0; k < R; ++k) if (i+k < nrow) {
				for (int j = 0; j < ncol; ++j)
					tmp[i+k][j] = '.';
			}
		}
		for (int j = 0; j < ncol; ++j) {
			bool work = false;
			for (int i = 0; i < nrow; ++i) if (tmp[i][j] == 'X') {
				work = true; break;
			}
			if (work) {
				move++;
				for (int k = 0; k < C; ++k) if (j+k < ncol) {
					for (int i = 0; i < nrow; ++i) tmp[i][j+k] = '.';
				}
			}
		}
		best = min(best, move);
	}
	return best;
}
};
