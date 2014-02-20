#include <vector>
#include <string>
using namespace std;


// brute force
// the best square has to start somewhere, so (s1, s2, size) denotes the best square start at (s1, s2) with length size
// then we can check whether this is possible or not by operating on the rows
class AlienAndGame
{
public:

bool isSquare(int s1, int s2, int size, const vector<string> &board)
{
	int nrow = board.size();
	int ncol = board[0].size();
	if (s1 + size > nrow || s2 + size > ncol) return false;
	
	for (int row = s1; row < s1 + size; row++) {
		char ch = board[row][s2];
		for (int col = s2; col < s2 + size; col++) {  // each row must be all 'W' or all 'B'
			if (board[row][col] != ch) return false;
		}
	}
	return true;
}


int getNumber(vector <string> board)
{
	for (int size = board.size(); size > 0; --size) {
		for (int s1 = 0; s1 < board.size(); ++s1)
		for (int s2 = 0; s2 < board[0].size(); ++s2)
			if (isSquare(s1, s2, size, board)) return size * size;
	}
	return 1;
}

};
